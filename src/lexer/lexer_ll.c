/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:21:06 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:28:59 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_strcmp_exact(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*new1;
	unsigned char	*new2;

	i = 0;
	new1 = (unsigned char *)s1;
	new2 = (unsigned char *)s2;
	if (!new1 || !new2)
		return (-1);
	while (new1[i] && new2[i] && (new1[i] - new2[i] == 0))
		i++;
	if (!new1[i] && new2[i])
		return (-1);
	else if (new1[i] && !new2[i])
		return (1);
	else if (!new1[i] && !new2[i])
		return (0);
	else
		return (new1[i] - new2[i]);
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
