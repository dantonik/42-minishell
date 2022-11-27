/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:16:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 09:41:12 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	remove_duo_c2_help(char *s, unsigned short *flags, int i, int *j)
{
	if (s[i + (*j)] == '\\')
			(*j)++;
	else if (s[i + (*j)] == '\'' && !((*flags) & DQ_FLAG))
	{
		(*flags) ^= SQ_FLAG;
		(*j)++;
		if (s[i + (*j)] == '\'')
		{
			(*flags) ^= SQ_FLAG;
			(*j)++;
			printf("in here\n");
		}
		s[i] = s[i + (*j)];
		return (true);
	}
	else if (s[i + (*j)] == '"' && !((*flags) & SQ_FLAG))
	{
		(*flags) ^= DQ_FLAG;
		(*j)++;
		if (s[i + (*j)] == '"')
		{
			(*flags) ^= DQ_FLAG;
			(*j)++;
		}
		s[i] = s[i + (*j)];
		return (true);
	}
	s[i] = s[i + (*j)];
	return (false);
}

void	remove_dup_c2(char *s)
{
	int				i;
	int				j;
	unsigned short	flags;

	i = 0;
	j = 0;
	flags = 0;
	while (s[i + j] != '\0')
	{
		if (remove_duo_c2_help(s, &flags, i, &j))
			continue ;
		i++;
	}
	s[i] = '\0';
}
