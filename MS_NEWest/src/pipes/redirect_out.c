/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/09 02:04:47 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	is_cmnd(t_head *head)
{
	t_node		*temp;
	t_bool		exists;

	temp = head->head;
	exists = FALSE;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMND && temp->cmnd_path != NULL)
			exists = TRUE;
		temp = temp->next;
	}
	return (exists);
}

static void	exit_free(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}


int	last_red_in(t_node *temp)
{
	int		last_red;

	while (temp && temp->type != PIPE)
	{
		if (temp->type == RED_OUT || temp->type == APPEND)
		{
			last_red = temp->pos;
		}
		temp = temp->next;
	}
	return (last_red);
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
	int	f_out;

	f_out = red_file(temp, append);
	temp->std_out[0] = 1;
	temp->std_out[1] = dup(1);
	if (dup2(f_out, STDOUT_FILENO) < 0)
		perror("dup2");
	// execve("/bin/ls", ft_split("ls", ' '), NULL);
	// dup2(temp->std_out[1], 1);
	// close(temp->std_out[1]);
	close(f_out);
}

static int	red_out_file_exists(t_head *head)
{
	t_node			*temp;
	int				f_out;
	int				last;

	temp = head->head;
	last = last_red_in(temp);
	while (temp && temp->type != PIPE && (temp->pos < last || !is_cmnd(head)))
	{
		if (temp->type == RED_OUT || temp->type == APPEND)
		{
			if (temp->type == RED_OUT)
				f_out = red_file(temp, FALSE);
			else if (temp->type == APPEND)
				f_out = red_file(temp, TRUE);
			if (f_out < 0)
				exit_free("red_out_file_exists1");
			close(f_out);
		}
		else if (temp->type == CMND && temp->cmnd_path == NULL)
			exit_free("red_out_file_exists2");
		temp = temp->next;
	}
	return (last);
}

void	redirect_out(t_head *head)
{
	t_node			*temp;
	int				f_out;
	int				last_red;

	temp = head->head;
	last_red = red_out_file_exists(head);
	while (temp && temp->type != PIPE)
	{
		if (temp->pos == last_red && is_cmnd(head))
		{
			if (temp->type == RED_OUT)
				setup_dup2(temp, FALSE);
			else if (temp->type == APPEND)
				setup_dup2(temp, TRUE);
			else if (temp->type == CMND && temp->cmnd_path == NULL)
				exit_free("redirect_out");
		}
		temp = temp->next;
	}
}
