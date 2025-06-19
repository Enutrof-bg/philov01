/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:28:50 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/19 10:28:52 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_set_philo(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i] = malloc(sizeof(t_philosophers) * (1));
		if (!(table->philo[i]))
		{
			// while free tout les philo en arriere
			exit(EXIT_FAILURE);
		}
		table->philo[i]->pos = i;
		table->philo[i]->dead = 0;
		table->philo[i]->eating = 0;
		table->philo[i]->sleeping = 0;
		table->philo[i]->thinking = 0;
		table->philo[i]->last_meal = 0;
		table->philo[i]->nbr_time_i_ate = 0;
		table->philo[i]->nbr_philo = table->nbr_philo;
		table->philo[i]->time_to_die = table->time_to_die;
		table->philo[i]->time_to_eat = table->time_to_eat;
		table->philo[i]->time_to_sleep = table->time_to_sleep;
		table->philo[i]->nbr_time_to_eat = table->nbr_time_to_eat;
		printf("i:%d nbr:%d ", i, table->philo[i]->nbr_philo);
		table->philo[i]->fork[0] = table->table_fork[table->philo[i]->pos % table->nbr_philo];
		table->philo[i]->fork[1] = table->table_fork[(table->philo[i]->pos + 1) % table->nbr_philo];
		printf("philo:%d a fork1:%d et fork2:%d\n", i, table->philo[i]->fork[0], table->philo[i]->fork[1]);
		i++;
	}
	table->philo[i] = NULL;
}

void ft_set_table(t_table *table, char **argv, int argc)
{
	table->nbr_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nbr_time_to_eat = -1;
	if (argc == 6)
		table->nbr_time_to_eat = ft_atoi(argv[5]);
	table->philo = malloc(sizeof(t_philosophers *) * (table->nbr_philo + 1));
	if (!(table->philo))
		exit(EXIT_FAILURE);
	table->table_fork = malloc(sizeof(int) * (table->nbr_philo));
	if (!(table->table_fork))
	{
		//free tout avant
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while (i < table->nbr_philo)
	{
		table->table_fork[i] = i;
		// printf("i:%d fork:%d\n", i, table->table_fork[i]);
		i++;
	}
	ft_set_philo(table);
}