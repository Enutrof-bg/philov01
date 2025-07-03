/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:47:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 14:47:20 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// void	precise_usleep(long usec, t_table *table)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_time_ms() * 1000;
// 	while (get_time_ms() * 1000 - start < usec)
// 	{
// 		if (get_int(&table->table_mutex, &table->end) == 1)
// 			break ;
// 		elapsed = get_time_ms() * 1000 - start;
// 		rem = usec - elapsed;
// 		if (rem > 1000)
// 		{
// 			usleep(rem / 2);
// 		}
// 		else
// 		{
// 			while (get_time_ms() * 1000 - start < usec)
// 			{
// 			}
// 		}
// 	}
// }
void	precise_usleep(long usec, t_table *table)
{
	long	start;

	start = get_time_ms() * 1000;
	while (get_time_ms() * 1000 - start < usec)
	{
		if (get_int(&table->table_mutex, &table->end) == 1)
			break ;
		usleep(100);
	}
}
