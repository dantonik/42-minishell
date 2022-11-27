/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:53:08 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/27 03:32:02 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	is_cm(t_node *temp, int direction)
{
	t_bool		exists;

	exists = FALSE;
	while (direction == 0 && temp->prev && temp->type != PIPE)
		temp = temp->prev;
	while (direction == 0 && temp->prev && temp->prev->type != PIPE)
		temp = temp->prev;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMND && temp->cmnd_path != NULL && direction != 1)
			exists = TRUE;
		temp = temp->next;
	}
	if (direction == 1)
	{
		if (temp)
			temp = temp->next;
		while (temp && temp->type != PIPE)
		{
			if (temp->type == CMND && temp->cmnd_path != NULL)
				exists = TRUE;
			temp = temp->next;
		}
	}
	return (exists);
}

int	ret(char *err, t_bool perr, int fd, int cmnd)
{
	if (fd > 2)
		close(fd);
	if (perr)
		perror(err);
	else
		printf("trash: %s\n", err);
	if (cmnd)
		return (-2);
	return (-1);
}

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

char	**split_paths(t_env_head *envp)
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

char	*ft_join_path(char *s1, char *s2)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(s1, "/");
	path = ft_strjoin(temp, s2);
	free(temp);
	return (path);
}
