/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:55:12 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/20 16:15:34 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtins(t_head **h)
{
	t_node	*c;

	if (h == NULL)
		return ;
	c = (*h)->head;
	while (c != NULL)
	{
		if (c->cmnd[0] == 'e' && c->cmnd[1] == 'c' && c->cmnd[2] \
			== 'h' && c->cmnd[3] == 'o' && (c->cmnd[4] == ' ' || c->cmnd[4] == '\0'))
			c->t_builtin = T_ECHO;
		if (c->cmnd[0] == 'c' && c->cmnd[1] == 'd' && (c->cmnd[2] == ' ' || c->cmnd[2] == '\0'))
			c->t_builtin = T_CD;
		if (c->cmnd[0] == 'p' && c->cmnd[1] == 'w' && c->cmnd[2] \
			== 'd' && (c->cmnd[3] == ' ' || c->cmnd[3] == '\0'))
			c->t_builtin = T_PWD;
		if (c->cmnd[0] == 'e' && c->cmnd[1] == 'x' && c->cmnd[2] \
			== 'p' && c->cmnd[3] == 'o' && c->cmnd[4] \
			== 'r' && c->cmnd[5] == 't' &&(c->cmnd[6] == ' ' || c->cmnd[6] == '\0'))
			c->t_builtin = T_EXPORT;
		if (c->cmnd[0] == 'u' && c->cmnd[1] == 'n' && c->cmnd[2] \
			== 's' && c->cmnd[3] == 'e' &&  c->cmnd[4] == 't' &&(c->cmnd[5] == ' ' || c->cmnd[5] == '\0'))
			c->t_builtin = T_UNSET;
		if (c->cmnd[0] == 'e' && c->cmnd[1] == 'n' && c->cmnd[2] \
			== 'v' && (c->cmnd[3] == ' ' || c->cmnd[3] == '\0'))
			c->t_builtin = T_ENV;
		if (c->cmnd[0] == 'e' && c->cmnd[1] == 'x' && c->cmnd[2] \
			== 'i' && c->cmnd[3] == 't' && (c->cmnd[4] == ' ' || c->cmnd[4] == '\0'))
			c->t_builtin = T_EXIT;
		c = c->next;
	}
}