/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/04 19:59:29 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_free(void)
{
	perror(MINISHELL);
	exit(EXIT_FAILURE);
}

static int	red_file(t_node *temp, t_bool append)
{
	int		f_out;
	int		space;
	char	*file;

	if (append == FALSE)
		space = 1;
	else
		space = 2;
	if (temp->cmnd[space] == ' ')
		file = ft_strdup(temp->cmnd + space + 1);
	else
		file = ft_strdup(temp->cmnd + space);
	if (append == FALSE)
	{
		f_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
		free(file);
	}
	else
		f_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	return (f_out);
}

static void	setup_dup2(t_node *temp, t_bool append)
{
	int	saved_stdin;
	int	f_out;

	f_out = red_file(temp, append);
	saved_stdin = dup(1);
	if (dup2(f_out, STDOUT_FILENO) < 0)
		perror("dup2");
	execve("/bin/ls", ft_split("ls", ' '), NULL);
	dup2(saved_stdin, 1);
	close(saved_stdin);
	close(f_out);
}

static int	red_out_file_exists(t_head *head)
{
	t_node			*temp;
	int				f_out;
	int				count_files;

	temp = head->head;
	count_files = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == RED_OUT || temp->type == APPEND)
		{
			if (temp->type == RED_OUT)
				f_out = red_file(temp, FALSE);
			else if (temp->type == APPEND)
				f_out = red_file(temp, TRUE);
			if (f_out < 0)
				exit_free();
			close(f_out);
			count_files++;
		}
		temp = temp->next;
	}
	return (count_files);
}

void	redirect_out(t_head *head)
{
	t_node			*temp;
	int				f_out;
	int				last_red;
	int				count;

	temp = head->head;
	last_red = red_out_file_exists(head);
	count = 0;
	while (temp && temp->type != PIPE)
	{
		if (++count == last_red)
		{
			if (temp->type == RED_IN)
				setup_dup2(temp, FALSE);
			else if (temp->type == APPEND)
				setup_dup2(temp, TRUE);
		}
		temp = temp->next;
	}
}
