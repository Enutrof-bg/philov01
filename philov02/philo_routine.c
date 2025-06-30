/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:01:47 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/21 13:01:49 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_died(t_philosophers *philo)
{
	long elapsed;
	long time_to_die;

	if (get_int(&philo->je_mange, &philo->full))
	{
		return (0);
	}

	elapsed = gettime(MILLISECOND) - get_long(&philo->je_mange, &philo->last_meal);
	time_to_die = philo->table_p->time_to_die / 1000;

	if (elapsed > time_to_die)
	{
		return(1);
	}
	return (0);
}

int all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	int ret;

	ret = 0;
	// safe_mutex_handle(mutex, LOCK);
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
	{
		ret = 1;
	}

	// safe_mutex_handle(mutex, UNLOCK);
	pthread_mutex_unlock(mutex);
	return (ret);
}

void *monitor_dinner(void *data)
{
	t_table *table;
	int i;
	table = (t_table *)data;
	printf("..................................test1......................................\n");
	printf("nbr_threads:%ld nbr_philo%d\n",table->nbr_threads, table->nbr_philo);
	while (!all_threads_running(&table->table_mutex, &table->nbr_threads, table->nbr_philo))
	{
		// printf("..................................test2......................................\n");
	}
	printf("nbr_threads:%ld nbr_philo%d\n",table->nbr_threads, table->nbr_philo);
	printf("..................................test3......................................\n");
	while (get_int(&table->table_mutex, &table->end) == 0)
	{
		i = 0;
		// printf("..................................test4......................................\n");
		while (i < table->nbr_philo && get_int(&table->table_mutex, &table->end) == 0)
		{
			// printf("testtesttest");
			// printf("..................................test5......................................\n");
			if (philo_died(&table->philo[i]) == 1)
			{
				printf("..................................test6......................................\n");
				// set_int(&table->table_mutex, &table->end, 1);
				// printf("testtesttest");
				// write_status(DIED, &table->philo[i]);
				set_int(&table->table_mutex, &table->end, 1);
				printf("%ld philo %d died.\n", gettime(MILLISECOND) - table->start, table->philo[i].pos);
			}
			i++;
		}
	}

	return (NULL);
}

void wait_all_threads(t_table *table)
{
	while (get_int(&table->table_mutex, &table->all_ready) == 0)
	{

	}
}

void thinking(t_philosophers *philo)
{
	write_status(THINKING, philo);
}

void eat(t_philosophers *philo)
{
	// long elapsed;
	// printf("caca1\n");
	// printf("caca1234\n");
	safe_mutex_handle(&philo->fork_first->fork, LOCK);
	// pthread_mutex_lock(&philo->fork_first->fork);
	// printf("caca123\n");
	write_status(TAKE_FIRST_FORK, philo);
	// elapsed = gettime(MILLISECOND) - philo->table_p->start;
	// printf("%ld %d has taken his first fork n:%d.\n", elapsed, philo->pos, philo->fork_first->fork_id);
	// printf("caca12\n");
	safe_mutex_handle(&philo->fork_second->fork, LOCK);
	// pthread_mutex_lock(&philo->fork_second->fork);
	write_status(TAKE_SECOND_FORK, philo);
	// printf("caca2\n");
	set_long(&philo->je_mange, &philo->last_meal, gettime(MILLISECOND));
	philo->nbr_time_i_ate++;
	write_status(EATING, philo);
	precise_usleep(philo->table_p->time_to_eat, philo->table_p);
	if (philo->table_p->nbr_time_to_eat > 0
		&& philo->nbr_time_i_ate == philo->table_p->nbr_time_to_eat)
	{
		set_int(&philo->je_mange, &philo->full, 1);
		// set_int(&philo->je_mange, &philo->table_p->end, 1);
	}
	// safe_mutex_handle(&philo->fork_first->fork, UNLOCK);
	// safe_mutex_handle(&philo->fork_second->fork, UNLOCK);
	pthread_mutex_unlock(&philo->fork_first->fork);
	pthread_mutex_unlock(&philo->fork_second->fork);
	// printf("caca9\n");
}

void *routine(void *data)
{
	t_philosophers *philoso;

	philoso = (t_philosophers *)data;

	wait_all_threads(philoso->table_p); //todo
	printf("Thread finished.\n");

	set_long(&philoso->je_mange, &philoso->last_meal, gettime(MILLISECOND));

	increase_long(&philoso->table_p->table_mutex, &philoso->table_p->nbr_threads);

	printf("nbr_threads:%ld\n", philoso->table_p->nbr_threads);
	//set last meal time

	while (get_int(&philoso->table_p->table_mutex, &philoso->table_p->end) == 0)
	{
		//i am full
		// printf("test1\n");
		if (philoso->full == 1)
		{
			printf("Je suis calé wo (philo:%d)\n", philoso->pos);
			break ;
		}

		//2 eat
		eat(philoso);
		// printf("test2\n");
		//3 sleep
		write_status(SLEEPING, philoso);
		// printf("test3\n");
		precise_usleep(philoso->table_p->time_to_sleep, philoso->table_p);
		// printf("test4\n");
		//4 thinking
		thinking(philoso);
		// printf("test5\n");
	}

	return (NULL);
}

void *lone_philo(void *data)
{
	t_philosophers *philo;

	philo = (t_philosophers *)data;
	wait_all_threads(philo->table_p);
	set_long(&philo->je_mange, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table_p->table_mutex, &philo->table_p->nbr_threads);
	write_status(TAKE_FIRST_FORK, philo);
	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		usleep(200);
	}
	return (0);
}

void dinner_start(t_table *table)
{
	// int i = 0;

	if (table->nbr_time_to_eat == 0)
	{
		return ;
	}
	else if (table->nbr_philo == 1)
	{
		pthread_create(&table->philo[0].t1, NULL, &lone_philo, (void *)&table->philo[0]);
	}
	else
	{
		// while (i < table->nbr_philo)
		// {
		// 	safe_mutex_handle();
		// 	i++;
		// }
		ft_pthread_create(table);
		// pthread_create(&table->monitor, NULL, &monitor_dinner, (void *)&table);
		// pthread_create(&table->monitor, NULL, &monitor_dinner, (void *)&table);
		// pthread_create(&table->monitor, NULL, &monitor_dinner, (void *)&table);
	}


	table->start = gettime(MILLISECOND);
	printf("start:%ld\n", table->start);
	
	printf("allready:%d\n", table->all_ready);
	set_int(&table->table_mutex, &table->all_ready, 1);
	// pthread_mutex_lock(&table->table_mutex);
	// table->all_ready = 1;
	// pthread_mutex_unlock(&table->table_mutex);
	printf("allready:%d\n", table->all_ready);

	ft_pthread_join(table);
}

// void *routine(void *data)
// {
// 	(void)data;
// 	t_philosophers *philoso;

// 	philoso = (t_philosophers *)data;
	
// 	pthread_mutex_lock(&philoso->je_mange);
// 	printf("Thread is running...\n");
// 	usleep(1000000);
// 	printf("nbr_philo:%d ", philoso->nbr_philo);
// 	printf("thinking:%d\n", philoso->thinking);
// 	printf("Thread finished.\n");

// 	pthread_mutex_unlock(&philoso->je_mange);
	
// 	return (NULL);
// }

/*
void *routine(void *data)
{
	(void)data;
	t_philosophers *philoso;

	philoso = (t_philosophers *)data;

	pthread_mutex_lock(&philoso->je_mange);
	philoso->last_meal = philoso->table_p->start;
	pthread_mutex_unlock(&philoso->je_mange);

	pthread_mutex_lock(&philoso->table_p->table_fork[philoso->fork[0]].fork);
	printf("philo%d a pickup fork gauche\n", philoso->pos);

	pthread_mutex_lock(&philoso->table_p->table_fork[philoso->fork[1]].fork);
	printf("philo%d a pickup fork droite\n", philoso->pos);
	printf("philo%d Mange\n", philoso->pos);

	pthread_mutex_lock(&philoso->je_mange);
	philoso->last_meal = get_time_in_ms();
	philoso->nbr_time_i_ate++;
	pthread_mutex_unlock(&philoso->je_mange);

	usleep(philoso->table_p->time_to_eat);

	pthread_mutex_unlock(&philoso->table_p->table_fork[philoso->fork[1]].fork);
	pthread_mutex_unlock(&philoso->table_p->table_fork[philoso->fork[0]].fork);

	printf("philo%d sleep\n", philoso->pos);
	usleep(philoso->table_p->time_to_sleep);


	pthread_mutex_lock(&philoso->je_mange);
	philoso->last_meal = philoso->table_p->start;
	pthread_mutex_unlock(&philoso->je_mange);

	printf("philo%d thinking\n", philoso->pos);
	usleep(philoso->table_p->time_to_die);
	// printf("Thread is running...\n");
	// // printf("fork1:%d fork2:%d\n", philoso->fork[0], philoso->fork[1]);
	// pthread_mutex_lock(&philoso->table_p->table_fork[philoso->fork[0]]);
	// usleep(1000000);
	// // printf("Thread is running...\n");
	// printf("fork1:%d fork2:%d\n", philoso->fork[0], philoso->fork[1]);
	
	// printf("test\n");
	// pthread_mutex_unlock(&philoso->table_p->table_fork[philoso->fork[0]]);
	// printf("Thread finished.\n");
	return (NULL);
}
*/
/*
void *routine(void *data)
{
	(void)data;
	t_philosophers *philoso;

	philoso = (t_philosophers *)data;
	
	// pthread_mutex_lock(&philoso->table_p->test);
	printf("Thread is running...\n");
	usleep(1000000);
	while (philoso->last_meal != 1)
	{
		// if (philoso->nbr_philo <= 1)
		// {
		// 	philoso->dead = 1;
		// }
		// if (philoso->dead == 1)
		// 	philoso->table_p->dead_end = 1;
		pthread_mutex_lock(&philoso->fork_left);
		
		// usleep(1000000);
		while(philoso->table_p->table_fork[philoso->fork[0]] == 0 && philoso->last_meal == 0)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[0]] == 0)
			{
				philoso->table_p->table_fork[philoso->fork[0]] = 1;
				philoso->pickup[0] = 1;
				printf("philo%d a pickup fork gauche\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_left);

		pthread_mutex_lock(&philoso->fork_right);
		while(philoso->table_p->table_fork[philoso->fork[1]] == 0 && philoso->last_meal == 0)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[1]] == 0)
			{
				philoso->table_p->table_fork[philoso->fork[1]] = 1;
				philoso->pickup[1] = 1;
				printf("philo%d a pickup fork droit\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_right);


		if (philoso->table_p->table_fork[philoso->fork[0]] == 1
			&& philoso->table_p->table_fork[philoso->fork[1]] == 1
			&& philoso->pickup[0] == 1
			&& philoso->pickup[1] == 1)
		{
			philoso->last_meal = 1;
			printf("philo%d Mange\n", philoso->pos);
		}

		// pthread_mutex_lock(&philoso->table_p->test);
		// int i = 0;
		// while (i < philoso->nbr_philo)
		// {
		// 	// table->table_fork[i] = 0;
		// 	printf("i:%d fork:%d\n", i, philoso->table_p->table_fork[i]);
		// 	i++;
		// }
		// pthread_mutex_unlock(&philoso->table_p->test);


		pthread_mutex_lock(&philoso->fork_left);
		while(philoso->table_p->table_fork[philoso->fork[0]] == 1 && philoso->pickup[0] == 1)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[0]] == 1 && philoso->pickup[0] == 1)
			{
				philoso->table_p->table_fork[philoso->fork[0]] = 0;
				philoso->pickup[0] = 0;
				printf("philo%d a depose fork gauche\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_left);


		pthread_mutex_lock(&philoso->fork_right);
		while(philoso->table_p->table_fork[philoso->fork[1]] == 1 && philoso->pickup[1] == 1)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[1]] == 1 && philoso->pickup[1] == 1)
			{
				philoso->table_p->table_fork[philoso->fork[1]] = 0;
				philoso->pickup[1] = 0;
				printf("philo%d a depose fork droit\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_right);
		// printf("nbr_philo:%d ", philoso->nbr_philo);
		// printf("thinking:%d\n", philoso->thinking);
	}
	printf("Thread finished.\n");

	// pthread_mutex_unlock(&philoso->table_p->test);
	
	return (NULL);
}

*/







// void *routine(void *data)
// {
// 	(void)data;
// 	t_table *philoso;

// 	philoso = (t_table *)data;
// 	printf("Thread is running...\n");
// 	usleep(1000000);
// 	// pthread_mutex_lock(&philoso->je_mange);
// 	printf("nbr_philo:%d\n", philoso->nbr_philo);
// 	// pthread_mutex_unlock(&philoso->je_mange);
// 	printf("Thread finished.\n");
// 	return (NULL);
// }

// void ft_philo(t_philosophers *philo)
// {
// 	pthread_t t1;
// 	pthread_mutex_init(&philo->je_mange, NULL);
// 	pthread_create(&t1, NULL, &routine, (void *)philo);
// 	// pthread_create(&t2, NULL, &routine, (void *)philo);

// 	pthread_join(t1, NULL);
// 	// pthread_join(t2, NULL);

// 	pthread_mutex_destroy(&philo->je_mange);
// }
