/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:12:27 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/28 17:12:28 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void write_status(t_philo_status status, t_philosophers *philo)
{
	if (philo->full)
		return ;

	pthread_mutex_lock(&philo->table_p->write_mutex);

	long elapsed = gettime(MILLISECOND) - philo->table_p->start;

	if (status == TAKE_FIRST_FORK && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d has taken his first fork n:%d.\n", elapsed, philo->pos, philo->fork_first->fork_id);
	}
	else if (status == TAKE_SECOND_FORK && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d has taken his second forkn:%d.\n", elapsed, philo->pos, philo->fork_second->fork_id);
	}
	else if (status == EATING && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d is eating.\n", elapsed, philo->pos);
	}
	else if (status == SLEEPING && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d is sleeping.\n", elapsed, philo->pos);
	}
	else if (status == THINKING && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d is thinking.\n", elapsed, philo->pos);
	}
	else if (status == DIED && get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		printf("%ld %d died.\n", elapsed, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}
