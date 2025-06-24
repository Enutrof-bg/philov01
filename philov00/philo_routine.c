/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:01:47 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/21 13:01:49 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void *routine(void *data)
// {
// 	(void)data;
// 	t_philosophers *philoso;

// 	philoso = (t_philosophers *)data;
	
// 	pthread_mutex_lock(&philoso->je_mange);
// 	printf("Thread is running...\n");
// 	usleep(1000000);
// 	printf("nbr_philo:%d ", philoso->nbr_philo);
// 	printf("thinking:%d\n", philoso->thinking);
// 	printf("Thread finished.\n");

// 	pthread_mutex_unlock(&philoso->je_mange);
	
// 	return (NULL);
// }

void *routine(void *data)
{
	(void)data;
	t_philosophers *philoso;

	philoso = (t_philosophers *)data;
	
	// pthread_mutex_lock(&philoso->table_p->test);
	printf("Thread is running...\n");
	usleep(1000000);
	while (philoso->last_meal != 1)
	{
		if (philoso->nbr_philo <= 1)
		{
			philoso->dead = 1;
		}
		if (philoso->dead == 1)
			philoso->table_p->dead_end = 1;
		pthread_mutex_lock(&philoso->table_p->test);
		
		// usleep(1000000);
		while(philoso->table_p->table_fork[philoso->fork[0]] == 0 && philoso->last_meal == 0)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[0]] == 0)
			{
				philoso->table_p->table_fork[philoso->fork[0]] = 1;
				philoso->pickup[0] = 1;
				printf("philo%d a pickup fork gauche\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->table_p->test);

		pthread_mutex_lock(&philoso->fork_right);
		while(philoso->table_p->table_fork[philoso->fork[1]] == 0 && philoso->last_meal == 0)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[1]] == 0)
			{
				philoso->table_p->table_fork[philoso->fork[1]] = 1;
				philoso->pickup[1] = 1;
				printf("philo%d a pickup fork droit\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_right);


		if (philoso->table_p->table_fork[philoso->fork[0]] == 1
			&& philoso->table_p->table_fork[philoso->fork[1]] == 1
			&& philoso->pickup[0] == 1
			&& philoso->pickup[1] == 1)
		{
			philoso->last_meal = 1;
			printf("philo%d Mange\n", philoso->pos);
		}

		// pthread_mutex_lock(&philoso->table_p->test);
		// int i = 0;
		// while (i < philoso->nbr_philo)
		// {
		// 	// table->table_fork[i] = 0;
		// 	printf("i:%d fork:%d\n", i, philoso->table_p->table_fork[i]);
		// 	i++;
		// }
		// pthread_mutex_unlock(&philoso->table_p->test);


		pthread_mutex_lock(&philoso->fork_left);
		while(philoso->table_p->table_fork[philoso->fork[0]] == 1 && philoso->pickup[0] == 1)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[0]] == 1 && philoso->pickup[0] == 1)
			{
				philoso->table_p->table_fork[philoso->fork[0]] = 0;
				philoso->pickup[0] = 0;
				printf("philo%d a depose fork gauche\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_left);


		pthread_mutex_lock(&philoso->fork_right);
		while(philoso->table_p->table_fork[philoso->fork[1]] == 1 && philoso->pickup[1] == 1)
		{
			// usleep(1000000);
			printf("philo%d is thinking\n", philoso->pos);
			if (philoso->table_p->table_fork[philoso->fork[1]] == 1 && philoso->pickup[1] == 1)
			{
				philoso->table_p->table_fork[philoso->fork[1]] = 0;
				philoso->pickup[1] = 0;
				printf("philo%d a depose fork droit\n", philoso->pos);
			}
		}
		pthread_mutex_unlock(&philoso->fork_right);
		// printf("nbr_philo:%d ", philoso->nbr_philo);
		// printf("thinking:%d\n", philoso->thinking);
	}
	printf("Thread finished.\n");

	// pthread_mutex_unlock(&philoso->table_p->test);
	
	return (NULL);
}

// void *routine(void *data)
// {
// 	(void)data;
// 	t_table *philoso;

// 	philoso = (t_table *)data;
// 	printf("Thread is running...\n");
// 	usleep(1000000);
// 	// pthread_mutex_lock(&philoso->je_mange);
// 	printf("nbr_philo:%d\n", philoso->nbr_philo);
// 	// pthread_mutex_unlock(&philoso->je_mange);
// 	printf("Thread finished.\n");
// 	return (NULL);
// }

// void ft_philo(t_philosophers *philo)
// {
// 	pthread_t t1;
// 	pthread_mutex_init(&philo->je_mange, NULL);
// 	pthread_create(&t1, NULL, &routine, (void *)philo);
// 	// pthread_create(&t2, NULL, &routine, (void *)philo);

// 	pthread_join(t1, NULL);
// 	// pthread_join(t2, NULL);

// 	pthread_mutex_destroy(&philo->je_mange);
// }
