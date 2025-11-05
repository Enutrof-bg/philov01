/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:37:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/01 17:37:15 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_mort(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_int(&philo->je_mange, &philo->full) == 1)
		return (0);
	elapsed = get_time_ms() - get_long(&philo->je_mange, &philo->last_meal);
	time_to_die = philo->table_p->time_to_die / 1000;
	if (elapsed >= time_to_die)
		return (1);
	return (0);
}

void	*dinner_check(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (get_int(&table->table_mutex, &table->nbr_thread) != table->nbr_philo)
	{
	}
	while (1)
	{
		i = 0;
		while (i < table->nbr_philo
			&& get_int(&table->table_mutex, &table->end) == 0)
		{
			if (get_int(&table->table_mutex, &table->all_full)
				== table->nbr_philo)
				return (set_int(&table->table_mutex, &table->end, 1), NULL);
			if (philo_mort(&table->philo[i]) == 1)
			{
				return (ft_write(&table->philo[i], DEAD), NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->je_mange, &philo->last_meal, get_time_ms());
	increase_int(&philo->table_p->table_mutex, &philo->table_p->nbr_thread);
	while (get_int(&philo->table_p->table_mutex,
			&philo->table_p->end) == 0)
	{
		if (philo->full == 1)
		{
			increase_int(&philo->table_p->table_mutex,
				&philo->table_p->all_full);
			break ;
		}
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	*philo_solo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->je_mange, &philo->last_meal, get_time_ms());
	ft_write(philo, FORK1);
	while (get_int(&philo->table_p->table_mutex, &philo->table_p->end) == 0)
	{
		if (philo_mort(&philo->table_p->philo[0]) == 1)
		{
			ft_write(philo, DEAD);
			set_int(&philo->table_p->table_mutex, &philo->table_p->end, 1);
		}
	}
	return (NULL);
}

int	start_table(t_table *table)
{
	if (table->nbr_philo == 0 || table->nbr_time_to_eat == 0)
		return (0);
	else if (table->nbr_philo == 1)
	{
		if (pthread_create(&table->philo[0].t1, NULL,
				&philo_solo, (void *)&table->philo[0]) != 0)
			return (-1);
		set_long(&table->table_mutex, &table->start, get_time_ms());
		if (pthread_join(table->philo[0].t1, NULL) != 0)
			return (-1);
	}
	else if (table->nbr_philo >= 2)
	{
		set_long(&table->table_mutex, &table->start, get_time_ms());
		if (ft_create_thread(table) == -1)
			return (-1);
		if (ft_join_thread(table) == -1)
			return (-1);
	}
	return (0);
}
