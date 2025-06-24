/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:16:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/18 10:16:15 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc <= 4 || argc >= 7)
	{
		printf("arg error (4 ou 5)\n");
	}
	else if (argc >= 5 && argc <= 6)
	{
		if (ft_check_arg(argc, argv) == 0)
		{
			printf("error\n");
			return (1);
		}
		ft_set_table(&table, argv, argc);

		// struct timeval tv;
		// struct timeval test;
		// // time_t t;
		// gettimeofday(&tv, NULL);
		// usleep(50000);
		// gettimeofday(&test, NULL);

		// printf("1%ld\n 2%ld\n", tv.tv_sec, tv.tv_usec);
		// printf("1%ld\n 2%ld\n", test.tv_sec, test.tv_usec);
// 

		ft_pthread_mutex_init(&table);
		ft_pthread_create(&table);
		ft_pthread_join(&table);
		ft_pthread_mutex_destroy(&table);
		

		ft_free(&table);
	}
	// t_philosophers philo;

	// philo.nbr_philo = 5;
	// philo.time_to_die = 1000;
	// philo.time_to_eat = 100;
	// philo.time_to_sleep = 300;

	// (void)argc;
	// (void)argv;
	// pthread_t t1, t2;
	// pthread_mutex_init(&table.philo[1]->je_mange, NULL);
	// pthread_create(&t1, NULL, &routine, (void *)&table);
	// pthread_create(&t2, NULL, &routine, (void *)&table);

	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);

	// pthread_mutex_destroy(&table.philo[1]->je_mange);
	return (0);
}