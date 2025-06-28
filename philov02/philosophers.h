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
#include <errno.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}t_time_code;

struct s_table;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int fork_id;
}t_fork;

typedef struct s_philosophers
{
	int pos;
	// int fork[2];
	// int pickup[2];
	// unsigned int count;
	long last_meal;
	int nbr_time_i_ate;
	int full;
	pthread_t t1;
	// pthread_mutex_t je_mange;
	// pthread_mutex_t fork_left;
	// pthread_mutex_t fork_right;
	t_fork *fork_first;
	t_fork *fork_second;
	struct s_table *table_p;
}t_philosophers;

typedef struct s_table
{
	long start;//set
	int nbr_philo; //set
	long time_to_die;//set
	long time_to_eat;//set
	long time_to_sleep;//set
	int nbr_time_to_eat;//set
	t_fork *table_fork;
	int end;//set
	int all_ready;
	t_philosophers *philo;
	pthread_mutex_t table_mutex;
	pthread_mutex_t write_mutex;
}t_table;

//philo_routine.c
void *routine(void *data);
void dinner_start(t_table *table);

//philosophers_check.c
int ft_check_arg(int argc, char **argv);

//philo_free.c
void ft_free(t_table *table);
void error_exit(char *error);

//philo_init.c
void ft_set_table(t_table *table, char **argv, int argc);

//philosophers_utlis.c
long	ft_atoi(const char *str);
void *safe_malloc(size_t bytes);

//philo_pthread.c
void ft_pthread_mutex_init(t_table *table);
void ft_pthread_create(t_table *table);
void ft_pthread_join(t_table *table);
void ft_pthread_mutex_destroy(t_table *table);
void safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void handle_mutex_error(int status, t_opcode opcode);

//philo_time.c
time_t get_time_in_ms(void);
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);

void set_int(pthread_mutex_t *mutex, int *dest, int value);
void set_long(pthread_mutex_t *mutex, long *dest, long value);
int get_int(pthread_mutex_t *mutex, int *value);
long get_long(pthread_mutex_t *mutex, long *value);
int simulation_finished(t_table *table);


void wait_all_threads(t_table *table);



#endif