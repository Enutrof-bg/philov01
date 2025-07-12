/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:15:31 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/02 16:15:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
void	increase_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	increase_int(pthread_mutex_t *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
*/

void	increase_long_sem(sem_t *semaphore, long *value)
{
	sem_wait(semaphore);
	(*value)++;
	sem_post(semaphore);
}

void	increase_int_sem(sem_t *semaphore, int *value)
{
	sem_wait(semaphore);
	(*value)++;
	sem_post(semaphore);
}
