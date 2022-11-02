/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:40:02 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/02 14:24:12 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	trim_leading_char(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] == c)
		i++;
	if (i != 0)
	{
		j = 0;
		while (s[j + i] != '\0')
		{
			s[j] = s[j + i];
			j++;
		}
		s[j] = '\0';
	}
}

void	trim_trailing_char(char *s, char c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (s[i] == c)
			i--;
		else
			break ;
	}
	s[i + 1] = '\0';
}

void	remove_char(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			j = i;
			while (s[j] != '\0')
			{
				s[j] = s[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

int	ms_ispipe(int x)
{
	return (x == '<' || x == '|' || x == '>');
}
