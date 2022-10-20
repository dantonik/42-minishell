/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:46:16 by cboubour          #+#    #+#             */
/*   Updated: 2022/03/28 00:33:15 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t n)
{
	unsigned char	v;
	unsigned char	*ptr;

	v = val;
	ptr = dest;
	while (n > 0)
	{
		*ptr = val;
		ptr++;
		n--;
	}
	return (dest);
}
