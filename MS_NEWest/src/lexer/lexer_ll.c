/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:21:06 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/21 21:39:59 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_strcmp_exact(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*new1;
	unsigned char	*new2;

	i = 0;
	new1 = (unsigned char *)s1;
	new2 = (unsigned char *)s2;
	while (new1[i] && new2[i] && (new1[i] - new2[i] == 0))
		i++;
	if (!new1[i] && new2[i])
		return (-1);
	else if (new1[i] && !new2[i])
		return (1);
	else if (!new1[i] && !new2[i])
		return (0);
	else
		return (new1[i] - new2[i]);
}
