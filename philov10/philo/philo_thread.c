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

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->table_fork[i].fork, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&table->philo[i].je_mange, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (-1);
	return (0);
}

int	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i].t1, NULL,
				&routine, (void *)&table->philo[i]) != 0)
			return (-1);
		i++;
	}
	// if (pthread_create(&table->dinner, NULL,
	// 		&dinner_check, (void *)table) != 0)
	// 	return (-1);
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
	// if (pthread_join(table->dinner, NULL) != 0)
	// 	return (-1);
	return (0);
}

int	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_destroy(&table->philo[i].je_mange) != 0)
			return (-1);
		if (pthread_mutex_destroy(&table->table_fork[i].fork) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&table->table_mutex) != 0)
		return (-1);
	if (pthread_mutex_destroy(&table->write_mutex) != 0)
		return (-1);
	return (0);
}
