/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:51 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:27:52 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_set_table(t_table *table, int argc, char **argv)
{
	int i;

	i = 0;
	table->nbr_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * 1000;
	table->time_to_eat = ft_atoi(argv[3]) * 1000;
	table->time_to_sleep = ft_atoi(argv[4]) * 1000;
	table->nbr_time_to_eat = -1;
	if (argc == 6)
		table->nbr_time_to_eat = ft_atoi(argv[5]);
	table->end = 0;
	table->all_ready = 0;
	table->nbr_thread = 0;
	table->all_full = 0;

	table->philo = malloc(sizeof(t_philo) * table->nbr_philo);
	//protec malloc
	table->table_fork = malloc(sizeof(t_fork) * table->nbr_philo);
	//protec malloc
	while (i < table->nbr_philo)
	{
		table->philo[i].pos = i + 1;
		table->philo[i].full = 0;
		table->philo[i].nbr_time_i_ate = 0;
		table->philo[i].table_p = table;
		table->table_fork[i].id = i;
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		if (table->philo[i].pos % 2 == 0)
		{
			table->philo[i].fork_first = &table->table_fork[i];
			table->philo[i].fork_second = &table->table_fork[(i + 1) % table->nbr_philo];
		}
		else if (table->philo[i].pos % 2 == 1)
		{
			table->philo[i].fork_first = &table->table_fork[(i + 1) % table->nbr_philo];
			table->philo[i].fork_second = &table->table_fork[i];
		}
		printf("philo:%d fork1 n:%d fork2 n:%d\n", table->philo[i].pos, table->philo[i].fork_first->id,
			table->philo[i].fork_second->id);
		i++;
	}

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