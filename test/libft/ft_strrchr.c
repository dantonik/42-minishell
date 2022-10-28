/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:19:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/07 17:56:43 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_ptr;
	int		count;

	count = 0;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
		{
			last_ptr = ((char *)s);
			count++;
		}
		s++;
	}
	if ((unsigned char)c == '\0')
	{
		last_ptr = ((char *)s);
		return (last_ptr);
	}
	if (count > 0)
		return (last_ptr);
	return (NULL);
}
