/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pthread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:20:38 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/19 15:20:40 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	// safe_mutex_handle(mutex, LOCK);
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
	// safe_mutex_handle(mutex, UNLOCK);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

int get_int(pthread_mutex_t *mutex, int *value)
{
	int ret;

	// safe_mutex_handle(mutex, LOCK);
	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	// safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void increase_long(pthread_mutex_t *mutex, long *value)
{
	// long ret;

	safe_mutex_handle(mutex, LOCK);
	// ret = *value;
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
	// return (ret);
}

int simulation_finished(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end));
}

void ft_pthread_mutex_init(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		// pthread_create(&table->philo[i]->t1, NULL, &routine, (void *)table->philo[i]);
		safe_mutex_handle(&table->table_fork[i].fork, INIT);
		safe_mutex_handle(&table->philo[i].je_mange, INIT);
		table->table_fork[i].fork_id = i;
		i++;
	}
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	// safe_mutex_handle(&table->write_mutex, INIT);
	// int i;

	// i = 0;
	// while (i < table->nbr_philo)
	// {
	// 	// pthread_mutex_init(&table->philo[i]->je_mange, NULL);
	// 	// pthread_mutex_init(&table->test, NULL);
	// 	// pthread_mutex_init(&table->philo[i]->fork_left, NULL);
	// 	// pthread_mutex_init(&table->philo[i]->fork_right, NULL);
	// 	// pthread_mutex_init(&table->table_fork[i], NULL);
	// 	i++;
	// }
	// // pthread_mutex_init(&table->test, NULL);
}

void ft_pthread_create(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philo[i].t1, NULL, &routine, (void *)&table->philo[i]);
		// safe_mutex_handle(&table->table_fork[i].fork, INIT);
		table->table_fork[i].fork_id = i;
		i++;
	}
	// pthread_create(&table->monitor, NULL, &monitor_dinner, (void *)table);
}

void ft_pthread_join(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].t1, NULL);
		i++;
	}
	// pthread_join(table->monitor, NULL);
}

void ft_pthread_mutex_destroy(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->table_fork[i].fork);
		pthread_mutex_destroy(&table->philo[i].je_mange);
		// pthread_mutex_destroy(&table->philo[i]->je_mange);
		// pthread_mutex_destroy(&table->test);
		// pthread_mutex_destroy(&table->philo[i]->fork_left);
		// pthread_mutex_destroy(&table->philo[i]->fork_right);
		// pthread_mutex_destroy(&table->table_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	// safe_mutex_handle(&table->table_mutex, INIT);
	// safe_mutex_handle(&table->write_mutex, INIT);
}

void handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == UNLOCK || opcode == LOCK))
	{
		//destroy mutex
		error_exit("The value specified by mutex is invalid.2");
	}
	else if (status == EINVAL && (opcode == INIT))
	{
		//destroy mutex
		error_exit("The value specified by attr is invalid.1");
	}
	else if (status == EDEADLK)
	{
		//destroy mutex
		error_exit("A deadlock would occur if the thread waiting for mutex.");
	}
	else if (status == EPERM)
	{
		//destroy mutex
		error_exit("The cureent thread does not hold a lock on mutex.");
	}
	else if (status == ENOMEM)
	{
		//destroy mutex
		error_exit("The process cannot allocate enough memory to create another mutex.");
	}
	else if (status == EBUSY)
	{
		//destroy mutex
		error_exit("Mutex is locked");
	}
}

void safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
	{
		printf("wrong opcode");
		exit(EXIT_FAILURE);
	}
}