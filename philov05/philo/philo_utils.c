/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:28:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:28:20 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_write(t_philo *philo, int status)
{
	long	time;

	if (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0
		&& philo->full == 0)
	{
		time = get_time_ms() - philo->table_p->start;
		pthread_mutex_lock(&philo->table_p->write_mutex);
		if (status == SLEEP)
			printf("%ld philo %d is sleeping\n", time, philo->pos);
		else if (status == EAT)
			printf("%ld philo %d is eating\n", time, philo->pos);
		else if (status == THINK)
			printf("%ld philo %d is thinking\n", time, philo->pos);
		else if (status == DEAD)
			printf("%ld philo %d died\n", time, philo->pos);
		else if (status == FORK1)
			printf("%ld philo %d has taken a fork\n", time, philo->pos);
		else if (status == FORK2)
			printf("%ld philo %d has taken a fork\n", time, philo->pos);
		pthread_mutex_unlock(&philo->table_p->write_mutex);
	}
}

long	ft_atoi(const char *str)
{
	int		i;
	long	signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}
