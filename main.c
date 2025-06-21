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
			return (0);
		}
		ft_set_table(&table, argv, argc);

		// printf("nbr:%d die:%ld eat:%ld sleep:%ld b:%d\n",
		// 	table.nbr_philo,
		// 	table.time_to_die,
		// 	table.time_to_eat,
		// 	table.time_to_sleep,
		// 	table.nbr_time_to_eat);

		// int i = 0;
		// while (i < table.nbr_philo)
		// {
		// 	ft_philo(table.philo[i]);
		// 	i++;
		// }
		// struct  timeval tv;

		// gettimeofday(&tv, NULL);

		//test
		// pthread_t t1, t2, t3, t4, t5;
		// pthread_t t1, t2;
		// pthread_mutex_init(&table.test, NULL);
		// printf("testnbr_philo:%d\n", table.philo[0]->nbr_philo);
		// printf("testnbr_philo:%d\n", table.philo[1]->nbr_philo);

		// int i;
		ft_pthread_mutex_init(&table);
		ft_pthread_create(&table);
		ft_pthread_join(&table);
		ft_pthread_mutex_destroy(&table);

		
		// i = 0;
		// while (i < table.nbr_philo)
		// {
		// 	pthread_mutex_init(&table.philo[i]->je_mange, NULL);
		// 	i++;
		// }
		// // pthread_mutex_init(&table.philo[0]->je_mange, NULL);
		// // pthread_mutex_init(&table.philo[1]->je_mange, NULL);

		// i = 0;
		// while (i < table.nbr_philo)
		// {
		// 	pthread_create(&table.philo[i]->t1, NULL, &routine, (void *)table.philo[i]);
		// 	i++;
		// }
		// // pthread_create(&table.philo[0]->t1, NULL, &routine, (void *)&table.philo[0]);
		// // pthread_create(&table.philo[1]->t1, NULL, &routine, (void *)&table.philo[1]);

		// i = 0;
		// while (i < table.nbr_philo)
		// {
		// 	pthread_join(table.philo[i]->t1, NULL);
		// 	i++;
		// }
		// // pthread_join(table.philo[0]->t1, NULL);
		// // pthread_join(table.philo[1]->t1, NULL);

		// i = 0;
		// while (i < table.nbr_philo)
		// {
		// 	pthread_mutex_destroy(&table.philo[i]->je_mange);
		// 	i++;
		// }
		// pthread_mutex_destroy(&table.test);
		// pthread_mutex_destroy(&table.philo[0]->je_mange);
		// pthread_mutex_destroy(&table.philo[0]->je_mange);

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