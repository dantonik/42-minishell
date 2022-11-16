/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:00:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/16 22:45:34 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_funcs(t_node *temp)
{
	if (!temp->next || temp->next->type == PIPE)
	{
		close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd[WRITE]);
		return (exit_free("syntax error near unexpected token `|'"));
	}
	if (redirect_in(temp) == -1)
	{
		close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd[WRITE]);
		return (-1);
	}
	if (redirect_out(temp) == -1)
	{
		close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd[WRITE]);
		return (-1);
	}
	temp->head->current = execute(temp);
	return (0);
}

int	main_loop(t_head *head, t_env_head *envp)
{
	head->current = head->head;
	if (head->current->type == PIPE)
		return (exit_free("syntax error near unexpected token `|'"));
	validate(head->current, envp);
	while (head->current)
	{
		if (pipe(head->pipe_fd) == -1)
			perror(MINISHELL);
		if (head->current->type == PIPE)
		{
			if (exec_funcs(head->current->next) == -1)
				return (-1);
		}
		else if (exec_funcs(head->current) == -1)
			return (-1);
	}
	while (head->cnt_pid > 0)
	{
		waitpid(0, &(head->pid), 0);
		head->cnt_pid--;
	}
	return (0);
}

int	pipe_in_out(t_node *current)
{
	t_node		*temp;
	int			res;

	res = -1;
	temp = current;
	if (temp->type == PIPE)
	{
		res = 0;
		temp = temp->next;
	}
	while (temp && temp->type != PIPE)
		temp = temp->next;
	if (temp)
	{
		if (temp->type == PIPE && res != 0)
			res = 1;
		else if (temp->type == PIPE && res == 0)
			res = P_BOTH;
	}
	return (res);
}

void	pipes_child(t_node *temp, char **command)
{
	int	pipe_loc;
	int	read_pipe;

	pipe_loc = pipe_in_out(temp->head->current);
	if (temp->head->std_input[0] != 1 && (pipe_loc == 0 || pipe_loc == P_BOTH))
	{
		if (dup2(temp->head->temp_fd, STDIN_FILENO) != -1)
			close(temp->head->temp_fd);
		else
			perror("dup2 in fork");
	}
	if (temp->head->std_output[0] != 1 && (pipe_loc == 1 || pipe_loc == P_BOTH))
	{
		if (dup2(temp->head->pipe_fd[WRITE], STDOUT_FILENO) == -1)
			perror("dup2 in fork");
	}
	if (temp->head->std_input[0] == 1 && temp->head->temp_fd != -1)
		close(temp->head->temp_fd);
	close(temp->head->pipe_fd[READ]);
	close(temp->head->pipe_fd[WRITE]);
}

void	pipes_parent(t_node *temp)
{
	int	pipe_loc;

	pipe_loc = pipe_in_out(temp->head->current);
	if (temp->head->std_input[0] != 1 && (pipe_loc == 0 || pipe_loc == P_BOTH))
	{
		close(temp->head->temp_fd);
		if (pipe_loc != P_BOTH)
			close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd[WRITE]);
	}
	if (temp->head->std_output[0] != 1 && (pipe_loc == 1 || pipe_loc == P_BOTH))
	{
		if (pipe_loc != P_BOTH)
			close(temp->head->pipe_fd[WRITE]);
		temp->head->temp_fd = temp->head->pipe_fd[READ];
	}
	if (temp->head->std_input[0] == 1 && pipe_loc != 1)
	{
		close(temp->head->temp_fd);
		close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd[WRITE]);
	}
}
