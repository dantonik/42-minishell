/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/26 03:52:56 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	red_file(t_node *temp, t_bool heredoc, char **file)
{
	int		f_in;
	int		space;
	char	*temp_file;

	temp_file = NULL;
	if (heredoc == FALSE)
	{
		file = &temp_file;
		space = 1;
	}
	else
		space = 2;
	if (temp->cmnd[space] == ' ')
		*file = ft_strdup(temp->cmnd + space + 1);
	else
		*file = ft_strdup(temp->cmnd + space);
	if (heredoc == FALSE)
	{
		f_in = open(*file, O_RDONLY);
		free(*file);
		return (f_in);
	}
	else if (pipe(temp->here_fd) == -1)
		perror(MINISHELL);
	return (0);
}

static int	setup_dup2(t_node *temp, int first_param, int second_param)
{
	if (first_param < 0)
		return (-1);
	temp->head->std_input[0] = 1;
	if (dup2(first_param, second_param) < 0)
		perror("dup2");
	return (0);
}

static void	use_heredoc(t_node *temp, t_bool just_print)
{
	char	*input;
	char	*delim;

	red_file(temp, TRUE, &delim);
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (just_print == FALSE)
		{
			write(temp->here_fd[WRITE], input, ft_strlen(input));
			write(temp->here_fd[WRITE], "\n", 1);
		}
		free(input);
		input = readline("> ");
	}
	if (just_print == FALSE)
	{
		close(temp->here_fd[WRITE]);
		setup_dup2(temp, temp->here_fd[READ], STDIN_FILENO);
		close(temp->here_fd[READ]);
	}
	free(input);
}

static int	red_in_file_exists(t_node *curr)
{
	t_node			*temp;
	int				f_in;
	int				last;

	temp = curr;
	last = last_red_in(temp, 0);
	while (temp && temp->type != PIPE && (temp->pos < last || !is_cm(curr, -1)))
	{
		if ((temp->type == RED_IN || temp->type == HEREDOC))
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, NULL);
				if (f_in < 0)
					return (ret("No such file or directory", FALSE, f_in, 0));
				close(f_in);
			}
			else if (temp->type == HEREDOC)
				use_heredoc(temp, TRUE);
		}
		else if (temp->type == CMND && temp->cmnd_path == NULL)
			return (ret("command not found", FALSE, f_in, 1));
		temp = temp->next;
	}
	return (last);
}

int	redirect_in(t_node *temp)
{
	int				f_in;
	int				last_red;

	last_red = red_in_file_exists(temp->head->current);
	if (last_red == -1 || last_red == -2)
		return (last_red);
	while (temp && temp->type != PIPE)
	{
		if (temp->pos == last_red && is_cm(temp->head->current, -1))
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, NULL);
				if (setup_dup2(temp, f_in, STDIN_FILENO) == -1)
					return (ret("No such file or directory", FALSE, f_in, 0));
				close(f_in);
			}
			else if (temp->type == HEREDOC)
				use_heredoc(temp, FALSE);
			else if (temp->type == CMND && temp->cmnd_path == NULL)
				return (ret("command not found", FALSE, f_in, 1));
		}
		temp = temp->next;
	}
	return (0);
}
