/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:37:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/01 17:37:15 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_mort(t_philo *philo)
{
	long elapsed;
	long time_to_die;

	if (get_int(&philo->je_mange, &philo->full) == 1)
		return (0);
	elapsed = get_time_ms() - get_long(&philo->je_mange, &philo->last_meal);
	time_to_die = philo->table_p->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

void *dinner_check(void *data)
{
	t_table *table;
	int i;
	long time;

	table = (t_table *)data;
	// printf("*****************testtestnbr_threads:%d\n", table->nbr_thread);
	while (get_int(&table->table_mutex, &table->nbr_thread) != table->nbr_philo)
	{
		// printf("nbr_threads:%d\n", table->nbr_thread);
		// printf("*****************testtestnbr_threads:%d\n", table->nbr_thread);
	}
	printf("*****************testtestnbr_threads:%d\n", table->nbr_thread);
	while (get_int(&table->table_mutex, &table->end) == 0)
	{
		i = 0;

		while (i < table->nbr_philo && get_int(&table->table_mutex, &table->end) == 0)
		{

			if (get_int(&table->table_mutex, &table->all_full) == table->nbr_philo)
			{
				set_int(&table->table_mutex, &table->end, 1);
			}
			if (philo_mort(&table->philo[i]) == 1)
			{
				pthread_mutex_lock(&table->write_mutex);
				time = get_time_ms() - table->start;
				printf("%ld philo %d died\n", time, table->philo[i].pos);
				pthread_mutex_unlock(&table->write_mutex);

				set_int(&table->table_mutex, &table->end, 1);
			}
			i++;
		}
	}

	printf(".........................Thread dinner terminated.........................\n");
	return (NULL);
}

void ft_eat(t_philo *philo)
{
	long time;

	// time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->fork_first->fork);



	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d pick first fork\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);



	pthread_mutex_lock(&philo->fork_second->fork);



	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d pick second fork\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);



	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);



	pthread_mutex_lock(&philo->je_mange);
	philo->nbr_time_i_ate++;
	pthread_mutex_unlock(&philo->je_mange);


	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf(".............................philo %d ate |%d| time..............................\n",philo->pos, philo->nbr_time_i_ate);


	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d eating\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);



	// pthread_mutex_lock(&philo->je_mange);
	// philo->last_meal = get_time_ms();
	// pthread_mutex_unlock(&philo->je_mange);

	precise_usleep(philo->table_p->time_to_eat, philo->table_p);
	// philo->nbr_time_i_ate++;
	// printf(".........philo:%d | nbr_time_i_ate:%d | nbr_time_to_eat:%d...............\n", philo->pos, philo->nbr_time_i_ate, philo->table_p->nbr_time_to_eat);
	if (philo->table_p->nbr_time_to_eat > 0 && philo->nbr_time_i_ate == philo->table_p->nbr_time_to_eat)
	{
		pthread_mutex_lock(&philo->je_mange);
		philo->full = 1;
		pthread_mutex_unlock(&philo->je_mange);
		// printf("..............................philo%d.est.full...................\n", philo->pos);
	}
	


	pthread_mutex_unlock(&philo->fork_first->fork);
	pthread_mutex_unlock(&philo->fork_second->fork);
}

void ft_sleep(t_philo *philo)
{
	long time;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	time = get_time_ms() - philo->table_p->start;
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo %d is sleeping\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	precise_usleep(philo->table_p->time_to_sleep, philo->table_p);
}

void ft_think(t_philo *philo)
{
	long time;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	time = get_time_ms() - philo->table_p->start;
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo %d is thinking\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}	

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf("***********************************Thread started**********************************\n");
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	while (get_int(&philo->table_p->table_mutex, &philo->table_p->all_ready) == 0)
	{
	}
	
	// printf("start2:%ld\n", get_long(&philo->table_p->table_mutex, &philo->table_p->start));
	set_long(&philo->je_mange, &philo->last_meal, get_time_ms());

	increase_int(&philo->table_p->table_mutex, &philo->table_p->nbr_thread);
	printf("nbr_threads:%d\n", philo->table_p->nbr_thread);
	// printf("lastmeal:%ld\n", philo->last_meal);

	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		if (philo->full == 1)
		{
			increase_int(&philo->table_p->table_mutex, &philo->table_p->all_full);
			pthread_mutex_lock(&philo->table_p->write_mutex);
			printf("///////////////////////////////////////Je suis full(philo n%d).........................\n", philo->pos);
			printf("**************************************allfull:%d\n", philo->table_p->all_full);
			pthread_mutex_unlock(&philo->table_p->write_mutex);
			break ;
		}
		//eat
		ft_eat(philo); //HAHAHAHAH IL VEUT PAS MANGER CORRECTEMENT 

		//sleep
		ft_sleep(philo);

		//think
		ft_think(philo);
	}

	// usleep(1);
	// sleep(1);
	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf(".........................Thread finished.........................\n");
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	return (NULL);
}

void ft_create_thread(t_table *table)
{
	int i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philo[i].t1, NULL, &routine, (void *)&table->philo[i]);
		i++;
	}
	pthread_create(&table->dinner, NULL, &dinner_check, (void *)table);
}

void ft_join_thread(t_table *table)
{
	int i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].t1, NULL);
		i++;
	}
	pthread_join(table->dinner, NULL);
}

void *philo_solo(void *data)
{
	t_philo *philo;
	long time;

	philo = (t_philo *)data;

	set_long(&philo->je_mange, &philo->last_meal, get_time_ms());
	time = get_time_ms() - philo->table_p->start;
	printf("%ld philo%d pick first fork\n", time, philo->pos);
	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		if (philo_mort(&philo->table_p->philo[0]) == 1)
		{
			pthread_mutex_lock(&philo->table_p->write_mutex);
			time = get_time_ms() - philo->table_p->start;
			printf("%ld philo %d died\n", time, philo->table_p->philo[0].pos);
			pthread_mutex_unlock(&philo->table_p->write_mutex);

			set_int(&philo->table_p->table_mutex, &philo->table_p->end, 1);
		}
	}
	return (NULL);
}

void start_table(t_table *table)
{
	// int i = 0;
	if (table->nbr_philo == 0)
		return ;
	else if (table->nbr_philo == 1)
	{
		pthread_create(&table->philo[0].t1, NULL, &philo_solo, (void *)&table->philo[0]);
		set_long(&table->table_mutex, &table->start, get_time_ms());
		pthread_join(table->philo[0].t1, NULL);
		return ;
	}
	else if (table->nbr_philo >= 2)
	{
		ft_create_thread(table);
		// while (i < table->nbr_philo)
		// {
		// 	// printf("%d\n", i);
		// 	pthread_create(&table->philo[i].t1, NULL, &routine, (void *)&table->philo[i]);
		// 	i++;
		// }
	}

	set_long(&table->table_mutex, &table->start, get_time_ms());
	// sleep(1);
	set_int(&table->table_mutex, &table->all_ready, 1);
	// printf("start1:%ld\n", table->start);
	ft_join_thread(table);
	// i = 0;
	// while (i < table->nbr_philo)
	// {
	// 	pthread_join(table->philo[i].t1, NULL);
	// 	i++;
	// }
}