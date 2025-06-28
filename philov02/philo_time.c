/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:25:26 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/23 11:25:27 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long get_time_in_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday() failed");
	return (tv.tv_sec *1000) + (tv.tv_usec / 1000);
}

long gettime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday() failed");
	else if (SECOND == time_code)
		return (tv.tv_sec) + (tv.tv_usec / 1000000);
	else if (MILLISECOND == time_code)
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1000000) + (tv.tv_usec);
	else
		error_exit("wrong input");
	return (1);
}

void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table) == 1)
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
		{
			usleep(rem / 2);
		}
		else
		{
			while (gettime(MICROSECOND) - start < usec)
			{

			}
		}
	}
}