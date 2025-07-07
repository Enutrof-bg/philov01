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

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		if (ft_check_arg(argc, argv) == 0)
			return (1);
		table = malloc(sizeof(t_table));
		if (!table)
			return (1);
		if (ft_set_table(table, argc, argv) == -1)
			return (ft_free(table), 1);
		ft_init_mutex(table);
		start_table(table);
		ft_mutex_destroy(table);
		ft_free(table);
	}
	return (0);
}
