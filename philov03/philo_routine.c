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

int get_int(pthread_mutex_t *mutex, int *val)
{
	int test;
	pthread_mutex_lock(mutex);
	test = *val;
	pthread_mutex_unlock(mutex);
	return (test);
}

long get_long(pthread_mutex_t *mutex, long *val)
{
	long test;
	pthread_mutex_lock(mutex);
	test = *val;
	pthread_mutex_unlock(mutex);
	return (test);
}

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

void *dinner_check(void *data)
{
	t_table *table;
	int i;
	long time;

	table = (t_table *)data;
	time = get_time_ms() - table->start;
	while (get_int(&table->table_mutex, &table->nbr_thread) == table->nbr_philo)
	{

	}
	while (get_int(&table->table_mutex, &table->end) == 0)
	{
		i = 0;
		while (i < table->nbr_philo && get_int(&table->table_mutex, &table->end) == 0)
		{
			if (philo_mort(&table->philo[i]) == 1)
			{
				pthread_mutex_lock(&table->write_mutex);
				printf("%ld philo%d died.\n", time, table->philo[i].pos);
				pthread_mutex_unlock(&table->write_mutex);

				pthread_mutex_lock(&table->table_mutex);
				table->end = 1;
				pthread_mutex_unlock(&table->table_mutex);
			}
			i++;
		}

	}

	return (NULL);
}


void ft_eat(t_philo *philo)
{
	long time;

	time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->fork_first->fork);

	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf("%ld philo%d pick first fork.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	pthread_mutex_lock(&philo->fork_second->fork);

	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf("%ld philo%d pick second fork.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf("%ld philo%d eating.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);

	usleep(philo->table_p->time_to_eat);
	philo->nbr_time_i_ate++;
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
	printf("%ld philo%d sleeping.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);

	usleep(philo->table_p->time_to_sleep);
}

void ft_think(t_philo *philo)
{
	long time;

	time = get_time_ms() - philo->table_p->start;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	printf("%ld philo%d thinking.\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	// printf("test1");
	while (get_int(&philo->table_p->table_mutex, &philo->table_p->all_ready) == 0)
	{}
	printf("..........philo%d..pret............test.....................................\n", philo->pos);

	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);

	pthread_mutex_lock(&philo->table_p->table_mutex);
	philo->table_p->nbr_thread++;
	pthread_mutex_unlock(&philo->table_p->table_mutex);

	printf("nbr_threads:%d\n", philo->table_p->nbr_thread);

	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0/* && philo->table_p->nbr_thread == philo->table_p->nbr_philo*/)
	{
		if (philo->full == 1)
		{
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
		// pthread_create(&table->dinner, NULL, &dinner_check, (void *)&table);
	}
	// printf("test1");
	pthread_mutex_lock(&table->table_mutex);
	table->start = get_time_ms();
	printf("start:%ld\n", table->start);
	pthread_mutex_unlock(&table->table_mutex);

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
	// pthread_join(table->dinner, NULL);
}