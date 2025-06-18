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

void *routine(void *data)
{
	(void)data;
	t_philosophers *philo;

	philo = (t_philosophers *)data;
	printf("Test thread\n");
	usleep(2000000);
	pthread_mutex_lock(&philo->count_mutex);
	printf("test:%d\n", philo->nbr_philo);
	pthread_mutex_unlock(&philo->count_mutex);
	printf("End\n");
	return (NULL);
}

int ft_check_max(char *argv)
{
	int result;
	int i;

	result = 0;
	i = 0;
	if (argv[i] == '+')
	{
		i++;
		if (!(argv[i] >= '0' && argv[i] <= '9'))
			return (0);
	}
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		if (result > (2147483647 - (argv[i] - '0')) / 10)
			return (0);
		result = result * 10 + argv[i] - '0';
		i++;
	}
	return (1);
}

int ft_check_negative(char *argv)
{
	if (argv[0] == '-')
		return (0);
	if (ft_atoi(argv) < 0)
		return (0);
	return (1);
}

int ft_check_arg(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		// printf("test\n");
		if (ft_check_max(argv[i]) == 0)
			return (0);
		if (ft_check_negative(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void ft_set_table(t_philosophers *table, char **argv, int argc)
{
	table->nbr_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nbr_time_to_eat = 0;
	if (argc == 6)
		table->nbr_time_to_eat = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_philosophers table;
	if (argc >= 5 && argc <= 6)
	{
		if (ft_check_arg(argc, argv) == 0)
		{
			printf("error\n");
			return (0);
		}
		ft_set_table(&table, argv, argc);
		printf("nbr:%d die:%ld eat:%ld sleep:%ld b:%d\n", table.nbr_philo,
			table.time_to_die, table.time_to_eat,
			table. time_to_sleep, table.nbr_time_to_eat);
	}
	else
	{

	}
	// t_philosophers philo;

	// philo.nbr_philo = 5;
	// philo.time_to_die = 1000;
	// philo.time_to_eat = 100;
	// philo.time_to_sleep = 300;

	// (void)argc;
	// (void)argv;
	// pthread_t t1, t2;
	// pthread_mutex_init(&philo.count_mutex, NULL);
	// pthread_create(&t1, NULL, &routine, (void *)&philo);
	// pthread_create(&t2, NULL, &routine, (void *)&philo);

	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);

	// pthread_mutex_destroy(&philo.count_mutex);
	return (0);
}