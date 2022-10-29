/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:07:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/25 00:38:57 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_pipe(t_head **head, char *str, char *input)
{
	int	i;
	int	j;

	if (input[0] == '<' && input[1] != '\0' && input[1] == '<')
	{
		i = 2;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		while (input[i] != '\0' && input[i] != ' ')
			i++;
		add_token_tail(head, ms_strdup(input, i), HEREDOC);
		return (i);
	}
	else if (input[0] == '<')
	{
		i = 1;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		while (input[i] != '\0' && input[i] != ' ')
			i++;
		add_token_tail(head, ms_strdup(input, i), RED_IN);
		return (i);
	}
	else if (input[0] == '>' && input[1] != '\0' && input[1] == '>')
	{
		add_token_tail(head, ft_strdup(">>"), APPEND);
		return (2);
	}
	else if (input[0] == '>')
		add_token_tail(head, ft_strdup(">"), RED_OUT);
	else
		add_token_tail(head, ft_strdup("|"), PIPE);
	return (1);
}

int ms_ispipe(int x)
{
	return x == '<' || x == '|' || x == '>';
}

int	create_token(t_head **head, char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (input[i] != '\0' && (ms_ispipe(input[i])))
		return (add_pipe(head, str, &input[i]));
	while (input[i] != '\0' && (!ms_ispipe(input[i])))
		i++;
	if (i == 0)
		return (0);
	add_token_tail(head, ms_strdup(input, i), 0);
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
		i += skip_whitespace(&input[i]);
	}
}