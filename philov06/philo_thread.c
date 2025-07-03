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

void	ft_init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_init(&table->table_fork[i].fork, NULL);
		pthread_mutex_init(&table->philo[i].je_mange, NULL);
		i++;
	}
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
}

void	ft_create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philo[i].t1, NULL,
			&routine, (void *)&table->philo[i]);
		i++;
	}
	// pthread_create(&table->dinner, NULL,
		// &dinner_check, (void *)table);
}

void	ft_join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].t1, NULL);
		i++;
	}
	// pthread_join(table->dinner, NULL);
}

void	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i].je_mange);
		pthread_mutex_destroy(&table->table_fork[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
}
