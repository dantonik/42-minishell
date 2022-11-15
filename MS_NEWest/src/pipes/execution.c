/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:22:15 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/15 01:45:55 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	my_free(char **arr)
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

	current = envp->head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, "PATH", 4))
		{
			paths = ft_split(current->value, ':');
			return (paths);
		}
		current = current->next;
	}
	return (NULL);
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

void	validate(t_head *head, t_env_head *envp)
{
	char			**command;
	char			**paths;
	char			*path;
	t_node			*temp;
	int				i;

	temp = head->head;
	while (temp)
	{
		if (temp->type == CMND)
		{
			command = ft_split(temp->cmnd, ' ');
			paths = split_paths(envp);
			if (paths == NULL)
				perror("validate");
			i = 0;
			while (paths[i])
			{
				path = ft_join_path(paths[i], '/', command[0]);
				if (access(path, F_OK | X_OK) == 0)
					temp->cmnd_path = ft_strdup(path);
				free(path);
				i++;
			}
			my_free(command);
			my_free(paths);
		}
		temp = temp->next;
	}
}

void	fork_exec(t_node *temp, char **command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork\n");
	temp->head->pid = pid;
	temp->head->cnt_pid++;
	if (pid == 0)
	{
		pipes_child(temp, command);
		// built_in(command);
		if (execve(temp->cmnd_path, command, NULL) == -1)
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
