/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/09 03:47:12 by dantonik         ###   ########.fr       */
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

//// BUILTINS
void		ft_echo(t_node *head, char *s);
void		check_builtins(t_head *head);
// ENV VARS
void		ft_env(t_env_head *head);
void		ft_export(t_env_head **head, char *cmnd);
void		ft_unset(t_env_head **head, char *s);

//// ENV ll
void		printl_export(t_env_head *head);
void		printl_env(t_env_head *head);
void		add_env_tail(t_env_head **head, char *key, char *value);
void		init_envs(t_env_head **head, char **env);
void		free_env_list(t_env_head *a);

//// EXPANDER
char		*expander(char *s, t_env_head *head);

//// LEXER
char		*add_until(t_head **head, char *input, int x, int type);
char		*add_pipe(t_head **head, char *input);
char		*add_cmnd(t_head **head, char *input);
char		*create_token(t_head **head, char *input);
void		create_list(t_head **head, char *input);
// LEXER ll
int			ms_ispipe(int x);
int			ms_strcmp_exact(const char *s1, const char *s2);

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

//// STRING BUILDER
t_stringbuilder	*sb_create(void);
int				sb_destroy(t_stringbuilder *sb);
int				sb_clear(t_stringbuilder *sb);
void			sb_copy_oldstr(t_stringbuilder *sb, char **newstr);

int				sb_append_char(t_stringbuilder *sb, char c);
int				sb_append_str(t_stringbuilder *sb, char *str);
int				sb_append_strn(t_stringbuilder *sb, char *str, int len);
int				sb_append_int(t_stringbuilder *sb, int nbr);
char			*sb_get_str(t_stringbuilder *sb);

#endif