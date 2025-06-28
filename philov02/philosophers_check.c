/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:20:10 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/19 10:20:11 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_check_max(char *argv)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while (argv[i] == ' ' || (argv[i] >= 9 && argv[i] <= 12))
		i++;
	if (argv[i] == '+')
		i++;
	else if (argv[i] == '-')
		return (0);
	if (!(argv[i] >= '0' && argv[i] <= '9'))
			return (0);
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