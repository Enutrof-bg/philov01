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

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_time_micro(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000000) + (tv.tv_usec));
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

void	ft_usleep(long usec, t_table *table, t_philo *philo)
{
	long	start;
	(void)table;
	start = get_time_ms() * 1000;
	while (get_time_ms() * 1000 - start < usec)
	{
		if (philo_mort(philo) == 1)
		{
			ft_write(philo, DEAD);
			return ;
		}
		if (get_int(&table->table_mutex, &table->end) == 1)
			return ;
		usleep(100);
	}
}

// void	ft_usleep(long usec, t_table *table)
// {
// 	long	start;

// 	start = get_time_ms() * 1000;
// 	while (get_time_ms() * 1000 - start < usec)
// 	{
// 		if (get_int(&table->table_mutex, &table->end) == 1)
// 			break ;
// 		usleep(100);
// 	}
// }
