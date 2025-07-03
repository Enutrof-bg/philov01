/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:36 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:27:39 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->table_fork)
		free(table->table_fork);
	free(table);
}
