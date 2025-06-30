/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:27:03 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/30 13:27:05 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	(void)argv;
	t_table *table;
	if (argc == 5 || argc == 6)
	{
		if (ft_check_arg(argc, argv) == 0)
		{
			printf("Error\nArg pas bon\n");
			return (0);
		}
		printf("Arg OK\n");

		table = malloc(sizeof(t_table));
		
		ft_set_table(table, argc, argv);

		start_table(table);
	}
	else 
	{
		printf("Arg error(4 ou 5)\n");
	}
	return (0);
}
