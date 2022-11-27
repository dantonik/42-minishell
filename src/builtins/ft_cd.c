/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:47:31 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/27 01:03:27 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ms_getenv(t_node *temp, char *str)
{
	t_env_node	*current;

	if (!str)
		return (NULL);
	current = temp->head->envp_ours->head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, str, ft_strlen(str) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*ms_checktilde(t_node *temp, char *str)
{
	if (*str == '~')
		return (ms_getenv(temp, "HOME"));
	else if (*str == '-')
		return (ms_getenv(temp, "OLDPWD"));
	else
		return (str);
}

static int	ms_putenv(t_node *temp, char *name, char *val)
{
	t_env_node	*curr_env;

	curr_env = temp->head->envp_ours->head;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->key, name, ft_strlen(name) + 1))
			break ;
		curr_env = curr_env->next;
	}
	if (curr_env)
	{
		free(curr_env->value);
		curr_env->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
		curr_env->value = ft_memcpy(curr_env->value, val, ft_strlen(val));
	}
	else
		return (ret("Path does not exist", FALSE, -1, 0));
	if (curr_env->value)
		return (0);
	else
		return (-1);
}

static int	ms_update_dir(t_node *temp)
{
	int		err;
	char	*new;

	err = 0;
	err = ms_putenv(temp, "OLDPWD", ms_getenv(temp, "PWD"));
	if (!err)
	{
		new = getcwd(NULL, 0);
		err = ms_putenv(temp, "PWD", new);
		free(new);
	}
	return (err);
}

int	ft_cd(t_node *temp)
{
	char	**command;
	int		err;

	if (temp->cmnd[2] && temp->cmnd[2] != ' ')
	{
		printf("trash: command not found\n");
		temp->t_builtin = 0;
		return (temp->head->exit_status = 127, -1);
	}
	command = ft_split(temp->cmnd, ' ');
	if (!command[1])
		err = chdir(ms_getenv(temp, "HOME"));
	else
		err = chdir(ms_checktilde(temp, command[1]));
	my_free(command);
	if (err)
		return (temp->head->exit_status = 1, ret("trash: cd", TRUE, -1, 0));
	else
		err = ms_update_dir(temp);
	return (err);
}
