/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:41:01 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/09 04:28:51 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_echo_flag(t_node *node, char *s)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	str = ft_split(s, ' ');
	while (str[i])
	{
		j = 0;
		if (ft_strncmp(str[i], "-n", 2) == 0)
		{
			node->echo_n = TRUE;
			j += 2;
			s += 2;
		}
		else
			return (s);
		while (str[i][j] && str[i][j] == 'n')
		{
			j++;
			s++;
		}
		i++;
		if (*s && *s == ' ')
			s++;
	}
	return (s);
}

void	ft_echo(t_node *node, char *s)
{
	int	i;

	s += 4;
	if (*s && *s != ' ')
	{
		printf("trash: command not found\n");
		return ;
	}
	s++;
	s = check_echo_flag(node, s);
	if (*s && *s == ' ')
		s++;
	while (*s != '\0')
	{
		write(1, s, 1);
		s++;
	}
	if (node->echo_n == FALSE)
		printf("\n");
}

void	check_builtins(t_head *head)
{
	t_node	*current;

	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		if (ft_strncmp(current->cmnd, "echo", 4) == 0)
		{
			current->t_builtin = T_ECHO;
			current->echo_n = FALSE;
		}
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