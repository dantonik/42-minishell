/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:59:14 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/27 09:00:18 by cboubour         ###   ########.fr       */
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
			return (my_free(str), s);
		while (str[i][j] && str[i][j++] == 'n')
			s++;
		i++;
		if (*s && *s == ' ')
			s++;
	}
	return (my_free(str), s);
}

void	ft_echo(t_node *node, char *s)
{
	s += 4;
	if (*s && *s != ' ')
	{
		printf("trash: command not found\n");
		node->t_builtin = 0;
		return ;
	}
	s++;
	remove_dup_c2(s);
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

void	ft_clear(char *s)
{
	if (ms_strcmp_exact("ft_clear", s) == 0)
		printf("\e[1;1H\e[2J");
	else
		printf("trash: command not found\n");
}

void	check_builtins(t_head *head)
{
	t_node	*current;

	current = head->head;
	while (current != NULL)
	{
		if (ft_strncmp(current->cmnd, "echo", 4) == 0)
			return (current->t_builtin = T_ECHO, \
			current->echo_n = FALSE, free_list(NULL));
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
		if (ft_strncmp(current->cmnd, "ft_clear", 8) == 0)
			current->t_builtin = T_CLEAR;
		current = current->next;
	}
}

void	built_in(t_env_head *envp, t_node *current, t_bool forked)
{
	if (current->t_builtin == T_ECHO)
		ft_echo(current, current->cmnd);
	current->head->e_s = 0;
	if (current->t_builtin == T_CD)
		ft_cd(current);
	if (current->t_builtin == T_PWD)
		ft_pwd();
	if (current->t_builtin == T_EXPORT)
		ft_export(&envp, current->cmnd);
	if (current->t_builtin == T_UNSET)
		ft_unset(&envp, current->cmnd, 1);
	if (current->t_builtin == T_ENV)
		printl_env(envp);
	if (current->t_builtin == T_EXIT)
		exit(exit_code(current));
	if (current->t_builtin == T_CLEAR)
		ft_clear(current->cmnd);
	if (forked)
		exit(EXIT_SUCCESS);
	else
		return ;
}
