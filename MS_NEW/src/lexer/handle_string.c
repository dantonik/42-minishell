/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:41:27 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/25 00:41:42 by dantonik         ###   ########.fr       */
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
	str = strip_multi_space(str);
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

int ms_iswhite(int x)
{
	return x == ' ' || x == '\t' || x == '\r' || x == '\n' || x == '\f';
}

int	skip_whitespace(char *input)
{
	int	i;

	i = 0;
	while (ms_iswhite(input[i]))
		i++;
	return (i);
}