/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:04:36 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/11 14:54:05 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	length;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start +1 || ft_strlen(s) == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	length = ft_strlen(s + start);
	if (len < length)
		length = len;
	ptr = (char *)malloc((length +1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s[start + i] != '\0' && len > 0)
	{
		ptr[i] = s[start + i];
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
