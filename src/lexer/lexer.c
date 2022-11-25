/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:07:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:29:30 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned short int	check_q(char input, unsigned short int flags)
{
	if (input == '\'' && !(flags & DQ_FLAG))
		flags ^= SQ_FLAG;
	else if (input == '"' && !(flags & SQ_FLAG))
		flags ^= DQ_FLAG;
	return (flags);
}

char	*add_cmnd(t_head **head, char *input)
{
	int					i;
	int					j;
	char				*s;
	unsigned short int	flags;

	flags = 0;
	j = 0;
	i = 0;
	while (input[j] != '\0' && input[j] == ' ')
		j++;
	while (input[j + i] != '\0')
	{
		flags = check_q(input[j + i], flags);
		if (flags & SQ_FLAG || flags & DQ_FLAG)
		{
			i++;
			continue ;
		}
		else if (ms_ispipe(input[i]))
			break ;
		i++;
	}
	if (i > 0)
		add_token_tail(head, ms_strdup(input, j + i), CMND);
	return (input + j + i);
}

char	*add_until(t_head **head, char *input, int x, int type)
{
	int		i;
	char	*str;

	i = x;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	while (input[i] != '\0' && (!ms_ispipe(input[i])) && input[i] != ' ')
		i++;
	str = ms_strdup(input, i);
	add_token_tail(head, str, type);
	return (input + i);
}

char	*add_pipe(t_head **head, char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (add_until(head, input, 2, HEREDOC));
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (add_until(head, input, 2, APPEND));
	else if (*input == '|')
		add_token_tail(head, ms_strdup("|", 1), PIPE);
	else if (*input == '<')
		return (add_until(head, input, 1, RED_IN));
	else if (*input == '>')
		return (add_until(head, input, 1, RED_OUT));
	return (input + 1);
}
