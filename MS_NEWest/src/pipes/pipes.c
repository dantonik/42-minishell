/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:00:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/15 01:39:03 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	main_loop(t_head *head, t_env_head *envp)
{
	head->current = head->head;
	validate(head, envp);
	while (head->current)
	{
		if (pipe(head->pipe_fd) == -1)
			perror(MINISHELL);
		if (head->current->type == PIPE)
		{
			redirect_in(head->current->next);
			redirect_out(head->current->next);
			head->current = execute(head->current->next);
		}
		else
		{
			redirect_in(head->current);
			redirect_out(head->current);
			head->current = execute(head->current);
		}
	}
	while (head->cnt_pid > 0)
	{
		waitpid(0, &(head->pid), 0);
		head->cnt_pid--;
	}
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
	if (temp->head->std_input[0] == 1)
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
	if (temp->head->std_input[0] == 1)
	{
		close(temp->head->temp_fd);
		close(temp->head->pipe_fd[READ]);
		if (temp->head->std_output[0] == 1)
			close(temp->head->pipe_fd[WRITE]);
	}
}
