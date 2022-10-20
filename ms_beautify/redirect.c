/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/21 01:41:24 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_in_file_exists(t_head *head)
{
	t_node			*temp;
	char			*file;
	int				f_in;
	int				count_files;

	temp = head->head;
	count_files = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RED_IN && !temp->t_builtin)
		{
			if (temp->cmnd[1] == ' ')
				file = ft_strdup(temp->cmnd + 2);
			else
				file = ft_strdup(temp->cmnd + 1);
			f_in = open(file, O_RDONLY);
			if (f_in < 0)
			{
				printf("trash-3.2: %s: No such file or directory\n", file);
				exit(EXIT_FAILURE);
			}
			count_files++;
			close(f_in);
		}
		temp = temp->next;
	}
	return (count_files);
}

void	redirect_in(t_head *head)
{
	t_node			*temp;
	char			*file;
	int				f_in;
	int				last_red;
	int				count;

	temp = head->head;
	last_red = red_in_file_exists(head);
	count = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RED_IN && !temp->t_builtin)
		{
			count++;
			if (count == last_red)
			{
				if (temp->cmnd[1] == ' ')
					file = ft_strdup(temp->cmnd + 2);
				else
					file = ft_strdup(temp->cmnd + 1);
				f_in = open(file, O_RDONLY);
				if (dup2(f_in, STDIN_FILENO) == -1)
					printf("ERROR on dup2 on input redirection");
				close(f_in);
				execve("/usr/bin/grep", ft_split("grep pa", ' '), NULL);
			}
		}
		temp = temp->next;
	}
}
