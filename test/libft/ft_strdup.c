/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:05:58 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/15 13:57:39 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		length;
	char	*ptr;

	length = ft_strlen(s1);
	ptr = (char *)malloc((length * sizeof(char)) + 1);
	if (ptr == NULL)
		return (0);
	while (*s1 != '\0')
	{
		*ptr = *s1;
		s1++;
		ptr++;
	}
	*ptr = '\0';
	ptr -= length;
	return (ptr);
}
