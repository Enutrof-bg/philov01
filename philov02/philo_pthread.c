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

void ft_pthread_mutex_init(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_init(&table->philo[i]->je_mange, NULL);
		// pthread_mutex_init(&table->test, NULL);
		pthread_mutex_init(&table->philo[i]->fork_left, NULL);
		pthread_mutex_init(&table->philo[i]->fork_right, NULL);
		pthread_mutex_init(&table->table_fork[i], NULL);
		i++;
	}
	// pthread_mutex_init(&table->test, NULL);
}

void ft_pthread_create(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philo[i]->t1, NULL, &routine, (void *)table->philo[i]);
		i++;
	}
}

void ft_pthread_join(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i]->t1, NULL);
		i++;
	}
}

void ft_pthread_mutex_destroy(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i]->je_mange);
		// pthread_mutex_destroy(&table->test);
		pthread_mutex_destroy(&table->philo[i]->fork_left);
		pthread_mutex_destroy(&table->philo[i]->fork_right);
		pthread_mutex_destroy(&table->table_fork[i]);
		i++;
	}
	// pthread_mutex_destroy(&table->test);
}
