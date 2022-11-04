/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/04 19:42:32 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_free(void)
{
	perror(MINISHELL);
	exit(EXIT_FAILURE);
}

static int	last_red_in(t_node *temp)
{
	int		last_red;

	while (temp && temp->type != PIPE)
	{
		if (temp->type == RED_IN || temp->type == HEREDOC)
		{
			last_red = temp->pos;
		}
		temp = temp->next;
	}
	return (last_red);
}

static int	red_file(t_node *temp, t_bool heredoc, char **file)
{
	int	f_in;
	int	space;

	if (heredoc == FALSE)
		space = 1;
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

static void	setup_dup2(int first_param, int second_param)
{
	int	saved_stdin;

	saved_stdin = dup(0);
	if (dup2(first_param, second_param) < 0)
		perror("dup2");
	// execve("/bin/cat", ft_split("cat", ' '), NULL);
	dup2(saved_stdin, 0);
	close(saved_stdin);
}

static void	use_append(t_node *temp, t_bool just_print)
{
	char	*input;
	char	*delim;

	red_file(temp, TRUE, &delim);
	printf("got in, %d, %s\n", just_print, delim);
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
		setup_dup2(temp->here_fd[READ], STDIN_FILENO);
	}
	free(input);
}

static int	red_in_file_exists(t_head *head, char **file)
{
	t_node			*temp;
	int				f_in;
	int				last;

	temp = head->head;
	last = last_red_in(temp);
	while (temp && temp->type != PIPE && temp->pos < last)
	{
		if ((temp->type == RED_IN || temp->type == HEREDOC))
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, file);
				if (f_in < 0)
					exit_free();
				close(f_in);
			}
			else if (temp->type == HEREDOC)
				use_append(temp, TRUE);
		}
		temp = temp->next;
	}
	return (last);
}

void	redirect_in(t_head *head)
{
	t_node			*temp;
	int				f_in;
	int				last_red;
	char			*file;

	temp = head->head;
	last_red = red_in_file_exists(head, &file);
	while (temp && temp->type != PIPE)
	{
		if (temp->pos == last_red)
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, &file);
				setup_dup2(f_in, STDIN_FILENO);
				close(f_in);
			}
			else if (temp->type == HEREDOC)
				use_append(temp, FALSE);
		}
		temp = temp->next;
	}
}
