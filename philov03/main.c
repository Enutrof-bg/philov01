/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:03 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:27:05 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_mutex_destroy(t_table *table)
{
	int i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i].je_mange);
		pthread_mutex_destroy(&table->table_fork[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
}

int main(int argc, char **argv)
{
	(void)argv;
	t_table *table;
	if (argc == 5 || argc == 6)
	{
		if (ft_check_arg(argc, argv) == 0)
		{
			printf("Error\nArg pas bon\n");
			return (0);
		}
		printf("Arg OK\n");

		table = malloc(sizeof(t_table));
		
		ft_set_table(table, argc, argv);

		printf("nbr_philo:%d\n", table->nbr_philo);

		start_table(table);

		ft_mutex_destroy(table);
		if (table->philo)
			free(table->philo);
		if (table->table_fork)
			free(table->table_fork);
		free(table);
	}
	else 
	{
		printf("Arg error(4 ou 5)\n");
	}
	return (0);
}
