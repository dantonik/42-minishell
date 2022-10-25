/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:32:19 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/18 14:39:51 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	length;
	char			nl;

	if (!s)
		return ;
	nl = '\n';
	length = ft_strlen(s);
	write(fd, s, length);
	write(fd, &nl, 1);
}
