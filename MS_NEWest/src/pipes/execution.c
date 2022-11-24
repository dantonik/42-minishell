/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:22:15 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/24 03:05:14 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	my_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free (arr);
}

static char	**split_paths(t_env_head *envp)
{
	char		**paths;
	t_env_node	*current;

	paths = NULL;
	current = envp->head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, "PATH", 4))
		{
			my_free(paths);
			paths = ft_split(current->value, ':');
			return (paths);
		}
		current = current->next;
	}
	return (paths);
}

static char	*ft_join_path(char *s1, char connector, char *s2)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(s1, "/");
	path = ft_strjoin(temp, s2);
	free(temp);
	return (path);
}

void	valid_check(t_node *temp, char **paths, char **command)
{
	int		i;
	char	*slash;
	char	*path;

	slash = ft_strchr(command[0], '/');
	if (slash)
	{
		if (access(command[0], F_OK | X_OK) == 0)
			temp->cmnd_path = ft_strdup(command[0]);
		return ;
	}
	i = 0;
	while (paths[i])
	{
		path = ft_join_path(paths[i], '/', command[0]);
		if (access(path, F_OK | X_OK) == 0)
			temp->cmnd_path = ft_strdup(path);
		free(path);
		i++;
	}
}

void	validate(t_node *temp, t_env_head *envp)
{
	char			**command;
	char			**paths;

	command = NULL;
	paths = NULL;
	while (temp)
	{
		if (temp->type == CMND)
		{
			command = ft_split(temp->cmnd, ' ');
			if (temp->t_builtin == 0)
			{
				paths = split_paths(envp);
				if (paths != NULL)
					valid_check(temp, paths, command);
				my_free(paths);
			}
			else
				temp->cmnd_path = ft_strdup(command[0]);
			my_free(command);
		}
		temp = temp->next;
	}
}

void	fork_exec(t_node *temp, char **command)
{
	int		pid;
	char	**envp_char;

	if (pipe_in_out(temp->head->current) == -1 && temp->t_builtin != 0)
		return (built_in(temp->head->envp_ours, temp, FALSE));
	pid = fork();
	if (pid == -1)
		perror("fork\n");
	temp->head->pid = pid;
	temp->head->cnt_pid++;
	if (pid == 0)
	{
		envp_char = path_str(temp->head->envp_ours);
		pipes_child(temp, command);
		if (temp->t_builtin != 0)
			built_in(temp->head->envp_ours, temp, TRUE);
		else if (execve(temp->cmnd_path, command, envp_char) == -1)
			perror("fork\n");
	}
	pipes_parent(temp);
}

t_node	*execute(t_node *temp)
{
	char			**command;

	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMND && temp->cmnd_path != NULL)
		{
			command = ft_split(temp->cmnd, ' ');
			fork_exec(temp, command);
			if (temp->head->std_input[0] == 1)
			{
				dup2(temp->head->std_input[1], 0);
				temp->head->std_input[0] = 0;
			}
			if (temp->head->std_output[0] == 1)
			{
				dup2(temp->head->std_output[1], 1);
				temp->head->std_output[0] = 0;
			}
			my_free(command);
		}
		temp = temp->next;
	}
	return (temp);
}
