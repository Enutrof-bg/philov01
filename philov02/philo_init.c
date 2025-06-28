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

void assign_fork(t_philosophers *philo, t_fork *fork, int position)
{
	int nbr_philo;

	nbr_philo = philo->table_p->nbr_philo;
	if (philo->pos % 2 == 0)
	{
		philo->fork_first = &fork[position];
		philo->fork_second = &fork[(position + 1) % nbr_philo];
	}
	else if (philo->pos % 2 == 1)
	{
		philo->fork_first = &fork[(position + 1) % nbr_philo];
		philo->fork_second = &fork[position];
	}
	printf("philo:%d first:%d second:%d\n",philo->pos, philo->fork_first->fork_id, philo->fork_second->fork_id);
}

void ft_set_philo(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
	{
		// table->philo[i] = malloc(sizeof(t_philosophers) * (1));
		// if (!(table->philo[i]))
		// {
		// 	// while free tout les philo en arriere
		// 	exit(EXIT_FAILURE);
		// }
		table->philo[i].table_p = table;
		table->philo[i].pos = i + 1;
		table->philo[i].nbr_time_i_ate = 0;
		table->philo[i].full = 0;
		// printf("i:%d nbr:%d ", i, table->philo[i]->nbr_philo);
		// table->philo[i]->fork[0] = table->table_fork[table->philo[i]->pos % table->nbr_philo];
		// table->philo[i]->fork[1] = table->table_fork[(table->philo[i]->pos + 1) % table->nbr_philo];
		// if (table->philo[i]->pos % 2 == 0)
		// {	
		// 	table->philo[i]->fork[0] = table->philo[i]->pos % table->nbr_philo;
		// 	table->philo[i]->fork[1] = (table->philo[i]->pos + 1) % table->nbr_philo;
		// }
		// if (table->philo[i]->pos % 2 == 1)
		// {
		// 	table->philo[i]->fork[1] = table->philo[i]->pos % table->nbr_philo;
		// 	table->philo[i]->fork[0] = (table->philo[i]->pos + 1) % table->nbr_philo;
		// }

		// // table->philo[i]->fork_left = table->table_fork[i % table->nbr_philo]->fork;
		// // table->philo[i]->fork_right = table->table_fork[(i + 1) % table->nbr_philo]->fork;
		// // printf("philo:%d a fork1:%d et fork2:%d\n", i, table->philo[i]->fork[0], table->philo[i]->fork[1]);
		
		// table->philo[i]->pickup[0] = 0;
		// table->philo[i]->pickup[1] = 0;
		assign_fork(&table->philo[i], table->table_fork, i);
		i++;
	}
	// table->philo[i] = NULL;
}

void ft_set_table(t_table *table, char **argv, int argc)
{
	table->nbr_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * 1000;
	table->time_to_eat = ft_atoi(argv[3]) * 1000;
	table->time_to_sleep = ft_atoi(argv[4]) * 1000;
	table->nbr_time_to_eat = -1;
	table->start = get_time_in_ms();
	if (argc == 6)
		table->nbr_time_to_eat = ft_atoi(argv[5]);
	printf("nbr philo:%d\ntimetodie:%ld\ntimetoeat:%ld\ntimetosleep:%ld\nnbrtimetoeat:%d\n",
		table->nbr_philo, table->time_to_die, table->time_to_eat,
		table->time_to_sleep, table->nbr_time_to_eat);
	if (table->time_to_die < 60000 || table->time_to_eat< 60000 || table->time_to_sleep < 60000)
	{
		printf("Error value <60ms\n");
		// exit(EXIT_FAILURE);
	}

	table->end = 0;
	table->all_ready = 0;
	table->philo = safe_malloc(sizeof(t_philosophers) * (table->nbr_philo));

	// table->table_fork = malloc(sizeof(t_fork *) * (table->nbr_philo));
	// if (!(table->table_fork))
	// {
	// 	//free tout avant
	// 	exit(EXIT_FAILURE);
	// }
	// int i = 0;
	// pthread_mutex_t *table_fork;

	table->table_fork = safe_malloc(sizeof(t_fork) * table->nbr_philo);
	// while (i < table->nbr_philo)
	// {
	// 	table->table_fork[i] = malloc(sizeof(t_fork));
	// 	// printf("i:%d fork:%d\n", i, table->table_fork[i]);
	// 	i++;
	// }
	//
	// 	int i;

	// i = 0;
	// while (i < table->nbr_philo)
	// {
	// 	// pthread_create(&table->philo[i]->t1, NULL, &routine, (void *)table->philo[i]);
	// 	safe_mutex_handle(table->table_fork.fork, INIT);
	// 	table->table_fork.fork_id = i;
	// 	i++;
	// }
	ft_pthread_mutex_init(table);

	ft_set_philo(table);
}