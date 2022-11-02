/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:07:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/02 14:21:51 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*add_until(t_head **head, char *input, int x, int type)
{
	int		i;

	i = x;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	while (input[i] != '\0' && (!ms_ispipe(input[i])))
		i++;
	add_token_tail(head, ms_strdup(input, i), type);
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
	char	*s;

	i = 0;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	while (input[i] != '\0' && (!ms_ispipe(input[i])))
		i++;
	s = ms_strdup(input, i);
	add_token_tail(head, ms_strdup(input, i), CMND);
	return (input + i);
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
