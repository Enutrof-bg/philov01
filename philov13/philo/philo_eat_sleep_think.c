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
	pthread_mutex_lock(&philo->fork_first->fork);
	ft_write(philo, FORK1);
	pthread_mutex_lock(&philo->fork_second->fork);
	ft_write(philo, FORK2);
	set_long(&philo->je_mange, &philo->last_meal, get_time_ms());
	increase_int(&philo->je_mange, &philo->nbr_time_i_ate);
	ft_write(philo, EAT);
	ft_usleep(philo->table_p->time_to_eat, philo->table_p);
	if (philo->table_p->nbr_time_to_eat > 0
		&& get_int(&philo->je_mange, &philo->nbr_time_i_ate)
		== philo->table_p->nbr_time_to_eat)
	{
		set_int(&philo->je_mange, &philo->full, 1);
	}
	pthread_mutex_unlock(&philo->fork_second->fork);
	pthread_mutex_unlock(&philo->fork_first->fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_write(philo, SLEEP);
	ft_usleep(philo->table_p->time_to_sleep, philo->table_p);
}

void	ft_think(t_philo *philo)
{
	long	think_time;

	ft_write(philo, THINK);
	if (philo->table_p->nbr_philo % 2 != 0)
	{
		think_time = (philo->table_p->time_to_eat * 2
				- philo->table_p->time_to_sleep);
		if (think_time < 0)
			think_time = 0;
		ft_usleep(think_time, philo->table_p);
	}
}
