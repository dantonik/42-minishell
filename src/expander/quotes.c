/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:16:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/28 04:34:19 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	setty(char *s, unsigned short *flags, char c, int *j)
{
	int	quotes_flag;

	quotes_flag = DQ_FLAG;
	if (c == '\'')
		quotes_flag = SQ_FLAG;
	(*flags) ^= quotes_flag;
	(*j)++;
	if (s[(*j)] == c)
	{
		(*flags) ^= quotes_flag;
		(*j)++;
	}
	*s = s[(*j)];
	return (true);
}

static t_bool	remove_quotes_helper(char *s, \
unsigned short *flags, int i, int *j)
{
	if (s[i + (*j)] == '\\')
			(*j)++;
	else if (s[i + (*j)] == '\'' && !((*flags) & DQ_FLAG))
	{
		return (setty(s + i, flags, '\'', j));
	}
	else if (s[i + (*j)] == '"' && !((*flags) & SQ_FLAG))
	{
		return (setty(s + i, flags, '"', j));
	}
	s[i] = s[i + (*j)];
	return (false);
}

void	remove_quotes(char *s)
{
	int				i;
	int				j;
	unsigned short	flags;

	i = 0;
	j = 0;
	flags = 0;
	while (s[i + j] != '\0')
	{
		if (remove_quotes_helper(s, &flags, i, &j))
			continue ;
		i++;
	}
	s[i] = '\0';
}
