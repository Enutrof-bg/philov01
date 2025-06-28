/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utlis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:54:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/18 14:54:20 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int	i;
	long	signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}

void *safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (!ret)
	{
		printf("error");
		exit(EXIT_FAILURE);
	}
	return (ret);
}