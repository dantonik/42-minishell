/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:00:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/14 00:08:17 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	main_loop(t_head *head, t_env_head *envp)
{
	head->current = head->head;
	validate(head, envp);
	while (head->current)
	{
		if (head->current->type == PIPE)
		{
			// redirect_in(head->current->next);
			// redirect_out(head->current->next);
			head->current = execute(head->current->next);
		}
		else
		{
			// redirect_in(head->current);
			// redirect_out(head->current);
			head->current = execute(head->current);
		}
		// exit(EXIT_FAILURE);
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
			res = PIPE_IN_OUT;
	}
	return (res);
}

// void	pipes(t_node *temp)
// {
// 	int	pipe_loc;

// 	pipe_loc = pipe_in_out(temp->head->current);
// 	// dprintf(temp->head->std_output[1], "std_output: %d, pipelock: %d\n", temp->head->std_output[0], pipe_loc);
// 	if (temp->head->std_input[0] != 1 && (pipe_loc == 0 || pipe_loc == PIPE_IN_OUT))
// 	{
// 		if (dup2(temp->head->pipe_fd[READ], STDIN_FILENO) != -1)
// 		{
// 			dprintf(temp->head->std_output[1], "inpipe\n");
// 			temp->head->pipe = pipe_loc;
// 			temp->head->std_input[0] = 1;
// 		}
// 		else
// 			perror("dup2 in pipes");
// 	}
// 	if (temp->head->std_output[0] != 1 && (pipe_loc == 1 || pipe_loc == PIPE_IN_OUT))
// 	{
// 		if (dup2(temp->head->pipe_fd[WRITE], STDOUT_FILENO) != -1)
// 		{
// 			temp->head->pipe = pipe_loc;
// 			temp->head->std_output[0] = 1;
// 			dprintf(temp->head->std_output[1], "outpipe \n");
// 		}
// 		else
// 			perror("dup2 in pipes");
// 	}
// }

void	pipes_child(t_node *temp, char **command)
{
	int	pipe_loc;
	int	read_pipe;

	pipe_loc = pipe_in_out(temp->head->current);
	// dprintf(temp->head->std_output[1], "cmnd1: %s, std_output: %d, pipelock: %d\n", command[0], temp->head->std_output[0], pipe_loc);
	if (temp->head->std_input[0] != 1 && pipe_loc == 0)
	{
		// dprintf(temp->head->std_output[1], "cmnd:%s ,pipe_fd[READ]:%d->0\n", command[0], temp->head->pipe_fd[READ]);
		if (temp->head->double_pipe == TRUE)
			read_pipe = temp->head->pipe_fd2[READ];
		else
		{
			read_pipe = temp->head->pipe_fd[READ];
		}
		if (dup2(read_pipe, STDIN_FILENO) != -1)
		{
			close(read_pipe);
		}
		else
			perror("dup2 in fork");
	}
	if (temp->head->std_output[0] != 1 && pipe_loc == 1)
	{
		// dprintf(temp->head->std_output[1], "cmnd:%s ,pipe_fd[WRITE]:%d->1\n", command[0], temp->head->pipe_fd[WRITE]);
		if (dup2(temp->head->pipe_fd[WRITE], STDOUT_FILENO) != -1)
		{
			close(temp->head->pipe_fd[WRITE]);
			close(temp->head->pipe_fd[READ]);
		}
		else
			perror("dup2 in fork");
	}
	if (temp->head->std_output[0] != 1 && pipe_loc == PIPE_IN_OUT)
	{
		if (dup2(temp->head->pipe_fd[READ], STDIN_FILENO) != -1)
		{
			close(temp->head->pipe_fd[READ]);
			// close(temp->head->pipe_fd[WRITE]);
		}
		else
			perror("dup2 in fork");
		if (dup2(temp->head->pipe_fd2[WRITE], STDOUT_FILENO) != -1)
		{
			close(temp->head->pipe_fd2[WRITE]);
			close(temp->head->pipe_fd2[READ]);

		}
	}
}

void	pipes_parent(t_node *temp)
{
	int	pipe_loc;

	pipe_loc = pipe_in_out(temp->head->current);
	// printf("std_output: %d, pipelock: %d\n", temp->head->std_output[0], pipe_loc);
	if (temp->head->std_input[0] != 1 && pipe_loc == 0)
	{
		// printf("inpipe\n");
		if (temp->head->double_pipe == TRUE)
			close(temp->head->pipe_fd2[READ]);
		else
			close(temp->head->pipe_fd[READ]);
	}
	if (temp->head->std_output[0] != 1 && pipe_loc == 1)
	{
		// printf("outpipe \n");
		close(temp->head->pipe_fd[WRITE]);
	}
	if (temp->head->std_output[0] != 1 && pipe_loc == PIPE_IN_OUT)
	{
		close(temp->head->pipe_fd[READ]);
		close(temp->head->pipe_fd2[WRITE]);
		temp->head->double_pipe = TRUE;
	}
	else
		temp->head->double_pipe = FALSE;
	temp->head->pipe = pipe_loc;
}
