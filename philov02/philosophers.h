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

struct s_table;

typedef struct s_philosophers
{
	int nbr_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int nbr_time_to_eat;
	int pos;
	int dead;
	int eating;
	int sleeping;
	int thinking;
	int last_meal;
	int nbr_time_i_ate;
	int fork[2];
	int pickup[2];
	// unsigned int count;
	pthread_t t1;
	pthread_mutex_t je_mange;
	pthread_mutex_t fork_left;
	pthread_mutex_t fork_right;
	struct s_table *table_p;
}t_philosophers;

typedef struct s_table
{
	int nbr_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int nbr_time_to_eat;
	int *table_fork;
	int dead_end;
	t_philosophers **philo;
	pthread_mutex_t test;
}t_table;

//philo_routine.c
void *routine(void *data);

//philosophers_check.c
int ft_check_arg(int argc, char **argv);

//philo_free.c
void ft_free(t_table *table);

//philo_init.c
void ft_set_table(t_table *table, char **argv, int argc);

//philosophers_utlis.c
int	ft_atoi(const char *str);

//philo_pthread.c
void ft_pthread_mutex_init(t_table *table);
void ft_pthread_create(t_table *table);
void ft_pthread_join(t_table *table);
void ft_pthread_mutex_destroy(t_table *table);

#endif