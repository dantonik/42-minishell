/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:16:17 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/20 00:40:33 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	static t_bool	valid;
	t_node			*temp;
	int				i;

	temp = head->head;
	while (temp)
	{
		if (temp->type == CMND)
		{
			valid = FALSE;
			command = ft_split(temp->cmnd, ' ');
			paths = split_paths(envp);
			if (paths == NULL)
				perror(MINISHELL);
			i = 0;
			while (paths[i])
			{
				path = ft_join_path(paths[i], '/', command[0]);
				if (access(path, F_OK | X_OK) == 0)
					valid = TRUE;
				free(path);
				i++;
			}
			if (!valid)
				temp->invalid = TRUE;
			my_free(command);
			my_free(paths);
		}
		temp = temp->next;
	}
}
