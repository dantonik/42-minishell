/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:41:27 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/02 14:18:47 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_strdup(char *input, int i)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (0);
	while (j < i)
	{
		str[j] = input[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*strip_multi_space(char *s)
{
	int			ij[2];
	int			count;
	char		*new;

	ij[0] = -1;
	ij[1] = 0;
	count = 0;
	while (s[++ij[0]] != '\0')
	{
		if (s[ij[0]] == ' ' || s[ij[0]] == '\t')
			count++;
		if (s[ij[0]] != ' ' && s[ij[0]] != '\t')
		{
			if (count >= 1)
			{
				count = 0;
				s[ij[1]++] = ' ';
			}
			s[ij[1]++] = s[ij[0]];
		}
	}
	s[ij[1]] = '\0';
	new = ft_strdup(s);
	free(s);
	return (new);
}

int	ms_iswhite(int x)
{
	return (x == ' ' || x == '\t' || x == '\r' || x == '\n' || x == '\f');
}

char	*skip_whitespace(char *input)
{
	while (ms_iswhite(*input))
		input++;
	return (input);
}

void	remove_dup_c(char *s, char c)
{
	int		i;
	int		j;
	bool	sq;
	bool	dq;

	i = 0;
	j = 0;
	sq = false;
	dq = false;
	while (s[i + j] != '\0')
	{
		if (s[i + j] == '\'')
			sq = !sq;
		if (s[i + j] == '"')
			dq = !dq;
		if (sq == false && dq == false && s[i + j] == c && s[i + j + 1] == c)
		{
			j++;
			continue ;
		}
		else
			s[i] = s[i + j];
		i++;
	}
	s[i] = '\0';
}
