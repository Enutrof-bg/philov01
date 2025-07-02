/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:28:00 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:28:00 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_mort(t_philo *philo)
{
	int test;
	long elapsed;
	long time_to_die;

	test = get_int(&philo->je_mange, &philo->full);
	if (test == 1)
		return (0);
	elapsed = get_time_ms() - get_long(&philo->je_mange, &philo->last_meal);
	time_to_die = philo->table_p->time_to_die / 1000;
	if (elapsed > time_to_die)
	{
		return (1);
	}
	return (0);
}

int all_threads_running(pthread_mutex_t *mutex, int *threads, int philo_nbr)
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

void *dinner_check(void *data)
{
	t_table *table;
	int i;
	long time;

	table = (t_table *)data;
	// time = get_time_ms() - table->start;
	pthread_mutex_lock(&table->table_mutex);
	printf("test......................nbr_thread%d nbr_philo%d........................\n", table->nbr_thread, table->nbr_philo);
	pthread_mutex_unlock(&table->table_mutex);
	while (!all_threads_running(&table->table_mutex, &table->nbr_thread, table->nbr_philo))
	{
		// printf("test......................nbr_thread%d nbr_philo%d........................\n", table->nbr_thread, table->nbr_philo);
	}
	printf("..........................dinner_check...............................\n");
	while (get_int(&table->table_mutex, &table->end) == 0)
	{
		i = 0;
		while (i < table->nbr_philo && get_int(&table->table_mutex, &table->end) == 0/* && get_int(&table->table_mutex, &table->all_full) == table->nbr_philo*/)
		{
			if (philo_mort(&table->philo[i]) == 1)
			{
				pthread_mutex_lock(&table->write_mutex);
				time = get_time_ms() - table->start;
				// if (get_int(&table->table_mutex, &table->end) == 0 && table->philo[i]->full == 0)
				printf("%ld philo%d died.\n", time, table->philo[i].pos);
				pthread_mutex_unlock(&table->write_mutex);

				pthread_mutex_lock(&table->table_mutex);
				table->end = 1;
				pthread_mutex_unlock(&table->table_mutex);
				printf("table->end:%d\n", table->end);
			}
			i++;
			printf("2:table->end:%d\n", table->end);
			sleep(1);
		}
		printf("3:table->end:%d\n", table->end);
	}
	printf(".............................Sortie de dinner_check()..................");
	return (NULL);
}

void wait_all_threads(t_table *table)
{
	while (get_int(&table->table_mutex, &table->all_ready) == 0)
	{

	}
}

void ft_eat(t_philo *philo)
{
	long time;

	time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->fork_first->fork);

	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo%d pick first fork.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	pthread_mutex_lock(&philo->fork_second->fork);

	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo%d pick second fork.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);

	philo->nbr_time_i_ate++;
	
	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo%d eating.\n", time, philo->pos);
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

	time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo%d sleeping.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	precise_usleep(philo->table_p->time_to_sleep, philo->table_p);
}

void ft_think(t_philo *philo)
{
	long time;

	time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0 && philo->full == 0)
		printf("%ld philo%d thinking.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	// printf("test1");
	// while (get_int(&philo->table_p->table_mutex, &philo->table_p->all_ready) == 0)
	// {}
	wait_all_threads(philo->table_p);
	printf("..........philo%d..pret............test.....................................\n", philo->pos);

	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);

	pthread_mutex_lock(&philo->table_p->table_mutex);
	philo->table_p->nbr_thread++;
	pthread_mutex_unlock(&philo->table_p->table_mutex);

	printf("nbr_threads:%d\n", philo->table_p->nbr_thread);

	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		/*&& get_int(&philo->table_p->table_mutex, &philo->table_p->all_ready) == 1*/)
	{
		if (philo->full == 1)
		{
			// pthread_mutex_lock(&philo->table_p->table_mutex);
			// philo->table_p->all_full++;
			// pthread_mutex_unlock(&philo->table_p->table_mutex);
			printf("Je suis full(philo %d)\n", philo->pos);
			break ;
		}

		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);

	}
	return (NULL);
}

void start_table(t_table *table)
{
	int i;

	i = 0;
	if (table->nbr_time_to_eat == 0)
		return ;
	else if (table->nbr_philo == 0)
	{

	}
	else 
	{
		while (i < table->nbr_philo)
		{
			pthread_create(&table->philo[i].t1, NULL, &routine, (void *)&table->philo[i]);
			i++;
		}
		pthread_create(&table->dinner, NULL, &dinner_check, (void *)table);
	}
	// printf("test1");
	
	// pthread_mutex_lock(&table->table_mutex);
	table->start = get_time_ms();
	printf("start:%ld\n", table->start);
	// pthread_mutex_unlock(&table->table_mutex);
	// sleep(2);
	
	printf("allready:%d\n", table->all_ready);
	pthread_mutex_lock(&table->table_mutex);
	table->all_ready = 1;
	pthread_mutex_unlock(&table->table_mutex);
	printf("allready:%d\n", table->all_ready);
	// // printf("test");

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].t1, NULL);
		i++;
	}
	pthread_join(table->dinner, NULL);
}