/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/24 23:24:59 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	temp->head->std_output[0] = 1;
	if (dup2(f_out, STDOUT_FILENO) < 0)
		perror("dup2");
	close(f_out);
}

static int	red_out_file_exists(t_node *curr)
{
	t_node			*temp;
	int				f_out;
	int				last;

	temp = curr;
	last = last_red_in(temp);
	while (temp && temp->type != PIPE && (temp->pos < last || !is_cmd(curr, -1)))
	{
		if (temp->type == RED_OUT || temp->type == APPEND)
		{
			if (temp->type == RED_OUT)
				f_out = red_file(temp, FALSE);
			else if (temp->type == APPEND)
				f_out = red_file(temp, TRUE);
			if (f_out < 0)
				return (ret("No such file or directory", FALSE, f_out, 0));
			close(f_out);
		}
		else if (temp->type == CMND && temp->cmnd_path == NULL)
			return (ret("command not found", FALSE, f_out, 1));
		temp = temp->next;
	}
	return (last);
}

int	redirect_out(t_node *current)
{
	t_node			*temp;
	int				last_red;

	temp = current;
	last_red = red_out_file_exists(current);
	if (last_red == -1 || last_red == -2)
		return (last_red);
	while (temp && temp->type != PIPE)
	{
		if (temp->pos == last_red && is_cmd(current, -1))
		{
			if (temp->type == RED_OUT)
				setup_dup2(temp, FALSE);
			else if (temp->type == APPEND)
				setup_dup2(temp, TRUE);
			else if (temp->type == CMND && temp->cmnd_path == NULL)
				return (ret("command not found", FALSE, -1, 1));
		}
		temp = temp->next;
	}
	return (0);
}
