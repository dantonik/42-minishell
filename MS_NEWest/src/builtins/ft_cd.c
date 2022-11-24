/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:47:31 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/24 00:15:09 by cboubour         ###   ########.fr       */
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
	if (!ft_strlen(str) || *str != '~' || !ms_getenv(temp, "HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(ms_getenv(temp, "HOME"), str));
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
		return (ret("Path does not exist", FALSE, -1));
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
	char	*new;

	command = ft_split(temp->cmnd, ' ');
	if (!command[1])
	{
		err = chdir(ms_getenv(temp, "HOME"));
		// printf("ms_getenv: %s, err: %d\n", ms_getenv(temp, "HOME"), err);
	}
	else
	{
		new = ms_checktilde(temp, command[1]);
		err = chdir(new);
		if (new)
			free(new);
	}
	if (err)
		return (ret("err in chdir", TRUE, -1));
	else
		err = ms_update_dir(temp);
	return (err);
}
