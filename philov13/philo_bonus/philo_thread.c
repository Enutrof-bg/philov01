/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:28:08 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:28:10 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_table *table)
{
	int	i;

	table->sem_fork = sem_open("/sem_fork", O_CREAT, 0644, table->nbr_philo);
	if (table->sem_fork == SEM_FAILED)
		return (1);
	table->sem_table = sem_open("/sem_table", O_CREAT, 0644, 1);
	if (table->sem_table == SEM_FAILED)
		return (1);
	table->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	if (table->sem_write == SEM_FAILED)
		return (1);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->table_fork[i].fork, NULL) != 0)
			return (-1);
		table->philo[i].sem_je_mange
			= sem_open("/sem_je_mange", O_CREAT, 0644, 1);
		if (table->philo[i].sem_je_mange == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (i % 2 == 0)
			if (pthread_create(&table->philo[i].t1, NULL,
					&routine, (void *)&table->philo[i]) != 0)
				return (-1);
		i++;
	}
	while (i-- > 0)
	{
		if (i % 2 == 1)
			if (pthread_create(&table->philo[i].t1, NULL,
					&routine, (void *)&table->philo[i]) != 0)
				return (-1);
	}
	if (pthread_create(&table->dinner, NULL,
			&dinner_check, (void *)table) != 0)
		return (-1);
	return (0);
}

int	ft_join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philo[i].t1, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(table->dinner, NULL) != 0)
		return (-1);
	return (0);
}

int	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_destroy(&table->table_fork[i].fork) != 0)
			return (-1);
		i++;
	}
	return (0);
}
