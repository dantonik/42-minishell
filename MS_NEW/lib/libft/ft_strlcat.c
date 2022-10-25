/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:55:59 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/11 14:58:49 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length_src;
	size_t	length_dest;

	length_dest = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (length_dest >= dstsize)
		return (dstsize + length_src);
	i = 0;
	while (src[i] && (length_dest + i) < (dstsize -1))
	{
		dst[length_dest + i] = src[i];
		i++;
	}
	dst[length_dest + i] = '\0';
	return (length_dest + length_src);
}
