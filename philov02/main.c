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
	t_table *table;


	if (argc <= 4 || argc >= 7)
	{
		printf("arg error (4 ou 5)\n");
	}
	else if (argc >= 5 && argc <= 6)
	{
		if (ft_check_arg(argc, argv) == 0)
		{
			printf("error argument\n");
			return (0);
		}
		table = malloc(sizeof(t_table));
		ft_set_table(table, argv, argc);

		// ft_pthread_mutex_init(table);
		// ft_pthread_create(table);
		// ft_pthread_join(table);
		// ft_pthread_mutex_destroy(table);
		dinner_start(table);
		ft_pthread_mutex_destroy(table);
		ft_free(table);
		free(table);
	}
	return (0);
}