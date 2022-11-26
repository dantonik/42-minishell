/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:00:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/27 00:35:32 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_funcs(t_node *temp, t_head *head, t_bool pipe)
{
	int	res;

	res = 0;
	if (pipe)
	{
		if (temp == NULL)
			res = -1;
		else if (temp->type == PIPE)
			res = -1;
		if (res == -1)
			printf("syntax error near unexpected token `|'\n");
	}
	if (res != -1)
		res = redirect_in(temp);
	if (res != -1 && res != -2)
		res = redirect_out(temp);
	temp->head->current = execute(temp);
	if (res == -1 || res == -2)
	{
		close(head->pipe_fd[READ]);
		close(head->pipe_fd[WRITE]);
	}
	return (res);
}

int	main_loop(t_head *head, t_env_head *envp)
{
	int	exec_ret;

	head->current = head->head;
	if (head->current->type == PIPE)
		return (ret("syntax error near unexpected token `|'", FALSE, -1, 0));
	validate(head->current, envp);
	while (head->current)
	{
		if (pipe(head->pipe_fd) == -1)
			perror(MINISHELL);
		if (head->current->type == PIPE)
			exec_ret = exec_funcs(head->current->next, head, TRUE);
		else
			exec_ret = exec_funcs(head->current, head, FALSE);
		if (exec_ret == -1)
			return (-1);
		else if (exec_ret == -2)
			continue ;
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

void	pipes_child(t_node *temp, char *command)
{
	int	pipe_loc;
	int	read_pipe;

	pipe_loc = pipe_in_out(temp->head->current);
	if (temp->head->std_input[0] != 1 && (pipe_loc == 0 || pipe_loc == P_BOTH))
	{
		if (is_cm(temp, 0))
		{
			if (dup2(temp->head->temp_fd, STDIN_FILENO) != -1)
				close(temp->head->temp_fd);
			else
				perror("dup2 input child fork");
		}
	}
	if (temp->head->std_output[0] != 1 && (pipe_loc == 1 || pipe_loc == P_BOTH))
	{
		if (dup2(temp->head->pipe_fd[WRITE], STDOUT_FILENO) == -1)
			perror("dup2 output child fork");
	}
	if (temp->head->std_input[0] == 1 && temp->head->temp_fd != -1)
		close(temp->head->temp_fd);
	close(temp->head->pipe_fd[READ]);
	close(temp->head->pipe_fd[WRITE]);
}

void	pipes_parent(t_node *temp, char *command)
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
