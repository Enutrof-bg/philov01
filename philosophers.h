/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:16:34 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/18 10:16:36 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h> //gettimeofday

typedef struct s_philosophers
{
	int nbr_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int nbr_time_to_eat;
	int dead;
	unsigned int count;
	pthread_mutex_t count_mutex;
}t_philosophers;

int	ft_atoi(const char *str);

#endif