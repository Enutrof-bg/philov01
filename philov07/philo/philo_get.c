/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:32:57 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/01 17:32:58 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_int(pthread_mutex_t *mutex, int *val)
{
	int	test;

	pthread_mutex_lock(mutex);
	test = *val;
	pthread_mutex_unlock(mutex);
	return (test);
}

long	get_long(pthread_mutex_t *mutex, long *val)
{
	long	test;

	pthread_mutex_lock(mutex);
	test = *val;
	pthread_mutex_unlock(mutex);
	return (test);
}

void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
