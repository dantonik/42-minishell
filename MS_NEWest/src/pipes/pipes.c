/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:00:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/09 01:00:23 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipes(t_bool red_in)
{
	if (pipe(pipe_fd) == -1)
		perror(MINISHELL);
	if (temp->std_in[0] != 1 && red_in)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror(MINISHELL);
	}
	if (temp->std_out[0] != 1 && !red_in)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror(MINISHELL);
	}
	// close(pipe_fd[0]);
	// close(pipe_fd[1]);
}
