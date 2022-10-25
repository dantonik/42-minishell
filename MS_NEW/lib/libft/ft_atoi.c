/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:39:30 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/10 01:45:41 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	unsigned int	i;
	int				count;
	long			number;

	i = 0;
	while (9 == str[i] || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 32)
		i++;
	count = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count *= -1;
		i++;
	}
	number = 0;
	while (47 < str[i] && str[i] < 58)
	{
		number = number * 10 + str[i] - 48;
		i++;
	}
	return (number * count);
}
