/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:39:07 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/19 16:59:47 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*string_1;
	unsigned char	*string_2;

	if (n <= 0)
		return (0);
	string_1 = (unsigned char *)s1;
	string_2 = (unsigned char *)s2;
	i = 0;
	while (string_1[i] == string_2[i] && n - 1 > i)
		i ++;
	if (i == n)
		return (0);
	return (string_1[i] - string_2[i]);
}
