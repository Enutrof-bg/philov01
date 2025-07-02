/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_sleep_think.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:18:57 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/02 16:18:58 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->fork_first->fork);
	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d pick first fork\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	pthread_mutex_lock(&philo->fork_second->fork);
	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d pick second fork\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	pthread_mutex_lock(&philo->je_mange);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->je_mange);
	pthread_mutex_lock(&philo->je_mange);
	philo->nbr_time_i_ate++;
	pthread_mutex_unlock(&philo->je_mange);
	pthread_mutex_lock(&philo->table_p->write_mutex);
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		printf("%ld philo%d eating\n", time, philo->pos);
	}
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	precise_usleep(philo->table_p->time_to_eat, philo->table_p);
	if (philo->table_p->nbr_time_to_eat > 0
		&& philo->nbr_time_i_ate == philo->table_p->nbr_time_to_eat)
	{
		pthread_mutex_lock(&philo->je_mange);
		philo->full = 1;
		pthread_mutex_unlock(&philo->je_mange);
	}
	pthread_mutex_unlock(&philo->fork_first->fork);
	pthread_mutex_unlock(&philo->fork_second->fork);
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	time = get_time_ms() - philo->table_p->start;
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
		printf("%ld philo %d is sleeping\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
	precise_usleep(philo->table_p->time_to_sleep, philo->table_p);
}

void	ft_think(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table_p->write_mutex);
	time = get_time_ms() - philo->table_p->start;
	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
		printf("%ld philo %d is thinking\n", time, philo->pos);
	pthread_mutex_unlock(&philo->table_p->write_mutex);
}
