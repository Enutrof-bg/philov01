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

void write_status(t_philo_status status, t_philo *philo)
{
	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (status == TAKE_FIRST_FORK || STATUS==TAKE_SECOND_FORK)
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}
