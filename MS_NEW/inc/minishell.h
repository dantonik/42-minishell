/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/25 00:44:23 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "\033[1;93mtrash-3.2$ \033[0;39m"

//// LEXER
int			add_pipe(t_head **head, char *str, char *input);
int			ms_ispipe(int x);
int			create_token(t_head **head, char *input);
void		create_list(t_head **head, char *input);
// HANDLE STRING
char		*ms_strdup(char *input, int i);
char		*strip_multi_space(char *s);
int			ms_iswhite(int x);
int			skip_whitespace(char *input);

//// LINKED LIST
void		add_token_tail(t_head **head, char *str, int type);
void		free_list(t_head *a);
void		printl(t_head *head);
void		free_list_loop(t_head **a);

#endif