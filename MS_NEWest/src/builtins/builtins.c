/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:41:01 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/02 15:08:36 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_builtins(t_head *head)
{
	t_node	*current;

	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		if (ft_strncmp(current->cmnd, "echo", 4) == 0)
			current->t_builtin = T_ECHO;
		if (ft_strncmp(current->cmnd, "cd", 2) == 0)
			current->t_builtin = T_CD;
		if (ft_strncmp(current->cmnd, "pwd", 3) == 0)
			current->t_builtin = T_PWD;
		if (ft_strncmp(current->cmnd, "export", 6) == 0)
			current->t_builtin = T_EXPORT;
		if (ft_strncmp(current->cmnd, "unset", 5) == 0)
			current->t_builtin = T_UNSET;
		if (ft_strncmp(current->cmnd, "env", 3) == 0)
			current->t_builtin = T_ENV;
		if (ft_strncmp(current->cmnd, "exit", 4) == 0)
			current->t_builtin = T_EXIT;
		current = current->next;
	}
}