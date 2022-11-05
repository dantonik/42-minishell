/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:22:15 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/04 23:50:40 by cboubour         ###   ########.fr       */
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
				perror(MINISHELL);
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

void	execute(t_head *head)
{
	char			**command;
	t_node			*temp;

	temp = head->head;
	while (temp)
	{
		if (temp->type == CMND && temp->cmnd_path != NULL)
		{
			command = ft_split(temp->cmnd, ' ');
			if (execve(temp->cmnd_path, command, NULL) == -1)
				perror(MINISHELL);
			my_free(command);
			if (temp->std_in[0] == 1)
			{
				dup2(temp->std_in[1], 0);
				close(temp->std_in[1]);
			}
			if (temp->std_out[0] == 1)
			{
				dup2(temp->std_out[1], 1);
				close(temp->std_out[1]);
			}
		}
		temp = temp->next;
	}
}
