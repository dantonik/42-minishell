/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:01:39 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/20 00:04:16 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	skip_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && (input[i] == ' ' || \
	input[i] == 13 || input[i] == 10 || input[i] == '\t'))
		i++;
	return (i);
}

int	create_token(t_head **head, char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (input[i] == '<' || input[i] == '|' || input[i] == '>')
	{
		str = (char *)malloc(sizeof(char) * (2));
		str[i] = input[i];
		str[i + 1] = '\0';
		add_token_tail(head, str, 6);
		return (1);
	}
	while (input[i] != '\0' && input[i] != '<' && \
	input[i] != '|' && input[i] != '>')
		i++;
	if (input[i] == '<' || input[i] == '|' || input[i] == '>')
		i--;
	str = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j <= i)
	{
		str[j] = input[j];
		j++;
	}
	str[j] = '\0';
	str = strip_multi_space(str);
	add_token_tail(head, str, 0);
	return (i);
}

void	create_list(t_head **head, char *input)
{
	int		i;

	i = 0;
	i = skip_whitespace(input);
	while (input[i] != '\0')
	{
		i += create_token(head, &input[i]);
		if (input[i] != '\0' && (input[i] == '<' || \
		input[i] == '|' || input[i] == '>'))
			i++;
		i += skip_whitespace(&input[i]);
	}
}
