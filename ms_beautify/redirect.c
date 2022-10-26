/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/25 21:29:50 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(void)
{
	perror(MINISHELL);
	exit(EXIT_FAILURE);
}

int	red_file(t_node *temp, t_bool heredoc, char **file)
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
	}
	else
		f_in = open(*file, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	return (f_in);
}

int	red_in_file_exists(t_head *head, char **file)
{
	t_node			*temp;
	int				f_in;
	int				count_files;

	temp = head->head;
	count_files = 0;
	while (temp && temp->type != PIPE && !temp->invalid)
	{
		if (temp->type == RED_IN || temp->type == HEREDOC)
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, file);
				if (f_in < 0)
					exit_free();
				close(f_in);
			}
			count_files++;
		}
		temp = temp->next;
	}
	return (count_files);
}

void	use_heredoc(t_node *temp)
{
	char	*input;
	char	*delim;
	int		f_in;
	int		saved_stdin;

	f_in = red_file(temp, TRUE, &delim);
	if (f_in < 0)
		exit_free();
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		write(f_in, input, ft_strlen(input));
		write(f_in, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	if (dup2(f_in, STDIN_FILENO) < 0)
		perror("dup2");
	execve("/bin/cat", ft_split("cat", ' '), NULL);
	// execve("/bin/echo", ft_split("echo 'lalalala'", ' '), NULL);
	close(f_in);
}

void	redirect_in(t_head *head)
{
	t_node			*temp;
	int				f_in;
	int				last_red;
	int				count;
	char			*file;
	int 			pid1;
	int				saved_stdin;

	file = NULL;
	temp = head->head;
	last_red = red_in_file_exists(head, &file);
	count = 0;
	while (temp && temp->type != PIPE && !temp->t_builtin && !temp->invalid)
	{
		if (++count == last_red)
		{
			if (temp->type == RED_IN)
			{
				f_in = red_file(temp, FALSE, &file);
				if (dup2(f_in, STDIN_FILENO) < 0)
					perror("dup2");
				close(f_in);
				// execve("/usr/bin/grep", ft_split("grep pa", ' '), NULL);
				execve("/bin/cat", ft_split("cat", ' '), NULL);
			}
			else if (temp->type == HEREDOC)
			{
				pid1 = fork();
				saved_stdin = dup(0);
				if (pid1 == -1)
					perror("error while forking");
				if (pid1 == 0)
					use_heredoc(temp);
				dup2(saved_stdin, 0);
				close(saved_stdin);
				waitpid(pid1, NULL, 0);
			}
		}
		temp = temp->next;
	}
}
