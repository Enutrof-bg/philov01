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
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

# define SLEEP 1
# define EAT 2
# define THINK 3
# define DEAD 4
# define FORK1 5
# define FORK2 6

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}t_fork;

typedef struct s_philo
{
	int				pos;
	int				full;
	int				nbr_time_i_ate;
	long			last_meal;
	pthread_t		t1;
	pthread_mutex_t	je_mange;
	t_fork			*fork_first;
	t_fork			*fork_second;
	struct s_table	*table_p;
}t_philo;

typedef struct s_table
{
	long			start;
	int				nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_time_to_eat;
	int				end;
	int				all_ready;
	int				nbr_thread;
	int				all_full;
	t_philo			*philo;
	t_fork			*table_fork;
	pthread_t		dinner;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
}t_table;

//philo_check
int		ft_check_arg(int argc, char **argv);

//philo_eat_sleep_think
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

//philo_free
void ft_free(t_table *table);

//philo_get
int		get_int(pthread_mutex_t *mutex, int *val);
long	get_long(pthread_mutex_t *mutex, long *val);
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);

//philo_get2.c
void	increase_long(pthread_mutex_t *mutex, long *value);
void	increase_int(pthread_mutex_t *mutex, int *value);

//philo_init
int		ft_set_table(t_table *table, int argc, char **argv);

//philo_routine
void	start_table(t_table *table);
void	*routine(void *data);
void	*dinner_check(void *data);

//philo_time
long	get_time_ms(void);
void	precise_usleep(long usec, t_table *table);

//philo_thread
void	ft_init_mutex(t_table *table);
void	ft_create_thread(t_table *table);
void	ft_join_thread(t_table *table);
void	ft_mutex_destroy(t_table *table);

//philo_utlis
long	ft_atoi(const char *str);
void	ft_write(t_philo *philo, int status);

#endif
