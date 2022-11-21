/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:07:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/21 21:40:21 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*add_cmnd(t_head **head, char *input)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	i = 0;
	while (input[j] != '\0' && input[j] == ' ')
		j++;
	while (input[j + i] != '\0' && (!ms_ispipe(input[j + i])))
		i++;
	if (i > 0)
	{
		s = ms_strdup(input, j + i);
		add_token_tail(head, s, CMND);
	}
	return (input + j + i);
}

char	*create_token(t_head **head, char *input)
{
	if (*input != '\0' && (ms_ispipe(*input)))
		return (add_pipe(head, input));
	if (*input != '\0' && (!ms_ispipe(*input)))
		return (add_cmnd(head, input));
	return (input);
}

void	create_list(t_head **head, char *input)
{
	int		i;

	i = 0;
	trim_leading_char(input, ' ');
	while (*input != '\0')
		input = create_token(head, input);
}
