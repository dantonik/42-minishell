/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:04:02 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/05 18:25:49 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length_count(int n)
{
	int	length;

	length = 0;
	if (!n)
		length = 1;
	if (n < 0)
	{
		length++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa_recursive(int n, char *number)
{
	int				length;

	length = ft_length_count(n);
	if (n < 0)
	{
		*number = '-';
		n *= -1;
	}
	number[length] = '\0';
	while (n)
	{
		number[length - 1] = (n % 10) + '0';
		n /= 10;
		length--;
	}
	return (number);
}

char	*ft_itoa(int n)
{
	char		*number;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	number = malloc((ft_length_count(n) + 1) * sizeof(char));
	if (!number)
		return (NULL);
	return (ft_itoa_recursive(n, number));
}
