/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:47:30 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/19 11:47:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void ft_free(t_table *table)
{
	int i;

	i = 0;
	if (table->table_fork)
		free(table->table_fork);
	if (table->philo)
		free(table->philo);
	// if (table->philo)
	// {
		// while (table->philo[i])
		// {
		// 	i++;
		// }
		// while (i > 0)
		// {
		// 	i--;
		// 	free(table->philo[i]);
		// }
		// free(table->philo);
	// }
}

void error_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}