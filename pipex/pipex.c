/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:19:23 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/16 19:59:00 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *cmd, char *envp[])
{
	int		i;
	char	**command;
	char	**paths;
	char	*path;

	command = ft_split(cmd, ' ');
	paths = split_paths(envp);
	if (paths == NULL)
		err_exit("Error: no PATH", command, paths);
	i = 0;
	while (paths[i])
	{
		path = ft_join_path(paths[i], '/', command[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (execve(path, command, NULL) == -1)
				err_exit("ERROR", command, paths);
		}
		free(path);
		i++;
	}
	my_free(command);
	my_free(paths);
}

static void	cmd1(int *pipe_fd, char **argv, char **envp)
{
	int		f_in;

	f_in = open(argv[1], O_RDONLY);
	if (f_in < 0)
		err_exit("ERROR (input file)", NULL, NULL);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		err_exit("ERROR", NULL, NULL);
	if (dup2(f_in, STDIN_FILENO) == -1)
		err_exit("ERROR", NULL, NULL);
	close(pipe_fd[0]);
	close(f_in);
	close(pipe_fd[1]);
	execute(argv[2], envp);
}

static void	cmd2(int *pipe_fd, char **argv, char **envp)
{
	int		f_out;

	f_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f_out < 0)
		err_exit("ERROR (output file)", NULL, NULL);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		err_exit("ERROR", NULL, NULL);
	if (dup2(f_out, STDOUT_FILENO) == -1)
		err_exit("ERROR", NULL, NULL);
	close(pipe_fd[1]);
	close(f_out);
	close(pipe_fd[0]);
	execute(argv[3], envp);
}

void	pipex(int argc, char *argv[], char *envp[])
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		err_exit("Error: wrong count of arguments", NULL, NULL);
	if (pipe(pipe_fd) == -1)
		err_exit("ERROR", NULL, NULL);
	pid1 = fork();
	if (pid1 == -1)
		err_exit("ERROR", NULL, NULL);
	if (pid1 == 0)
		cmd1(pipe_fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		err_exit("ERROR", NULL, NULL);
	if (pid2 == 0)
		cmd2(pipe_fd, argv, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}
