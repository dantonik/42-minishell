/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/16 21:54:57 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "\033[1;93mtrash-3.2$ \033[0;39m"
# define WRITE 1
# define READ 0
# define P_BOTH 10

//// BUILTINS
void		check_builtins(t_head *head);

//// ENV
void		printl_env(t_env_head *head);
void		add_env_tail(t_env_head **head, char *key, char *value);
void		init_envs(t_env_head **head, char **env);
void		free_env_list(t_env_head *a);

//// LEXER
char		*add_until(t_head **head, char *input, int x, int type);
char		*add_pipe(t_head **head, char *input);
char		*add_cmnd(t_head **head, char *input);
char		*create_token(t_head **head, char *input);
void		create_list(t_head **head, char *input);
// LEXER ll
int			ms_ispipe(int x);
// HANDLE STRING
char		*ms_strdup(char *input, int i);
char		*strip_multi_space(char *s);
int			ms_iswhite(int x);
char		*skip_whitespace(char *input);
void		remove_dup_c(char *s, char c);
// STRING UTILS
void		trim_leading_char(char *s, char c);
void		trim_trailing_char(char *s, char c);
void		remove_char(char *s, char c);

//// LINKED LIST
void		add_token_tail(t_head **head, char *str, int type);
void		free_list(t_head *a);
void		printl(t_head *head);
void		free_list_loop(t_head **a);

//// PIPES
int			redirect_in(t_node *head);
int			redirect_out(t_node *head);
void		validate(t_node *head, t_env_head *envp);
t_node		*execute(t_node *head);
void		pipes_child(t_node *temp, char **command);
void		pipes_parent(t_node *temp);
int			main_loop(t_head *head, t_env_head *envp);
int			pipe_in_out(t_node *current);
int			exit_free(char *err);

#endif
