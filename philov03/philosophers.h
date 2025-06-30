/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:12 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:27:13 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t fork;
	int id;
}t_fork;

typedef struct s_philo
{
	int pos;
	int full;
	int nbr_time_i_ate;
	long last_meal;
	pthread_t t1;
	pthread_mutex_t je_mange;
	t_fork *fork_first;
	t_fork *fork_second;
	struct s_table *table_p;
}t_philo;

typedef struct s_table
{
	long start;

	int nbr_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int nbr_time_to_eat;

	int end;
	int all_ready;
	int nbr_thread;

	t_philo *philo;
	t_fork *table_fork;
	pthread_t dinner;
	pthread_mutex_t table_mutex;
	pthread_mutex_t write_mutex;
}t_table;

//philo_check
int ft_check_arg(int argc, char **argv);

//philo_free

//philo_init
void ft_set_table(t_table *table, int argc, char **argv);

//philo_routine
void start_table(t_table *table);

//philo_time
long get_time_ms(void);

//philo_thread

//philo_utlis
long	ft_atoi(const char *str);


#endif
