/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:12:47 by cboubour          #+#    #+#             */
/*   Updated: 2022/07/04 00:09:48 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

void	pipex(int argc, char *argv[], char *envp[]);
char	**split_paths(char *envp[]);
char	*ft_join_path(char *s1, char connector, char *s2);
void	err_exit(char *err_msg, char **cmd, char **paths);
void	my_free(char **arr);

#endif
