/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:13 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/28 05:51:22 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "\033[1;93mtrash-3.2$ \033[0;39m"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct Node
{
	char			*cmnd;
	t_bool			invalid;
	enum
	{
		T_NOB,
		T_ECHO,
		T_CD,
		T_PWD,
		T_EXPORT,
		T_UNSET,
		T_ENV,
		T_EXIT
	}	t_builtin;
	enum
	{
		CMND,
		STRNG,
		RED_OUT,
		RED_IN,
		HEREDOC,
		APPEND,
		FILE_N,
		PIPE,
		SQ,
		DQ
	} type;
	int				length;
	struct Node		*next;
	struct Node		*prev;
}				t_node;

typedef struct linkedList
{
	int				length;
	int				pipes;
	int				cmnds;
	struct Node		*head;
	struct Node		*tail;
}				t_head;

typedef struct NodeEnv
{
	char			*key;
	char			*value;
	int				length;
	struct NodeEnv	*next;
	struct NodeEnv	*prev;
}				t_env_node;

typedef struct linkedListEnv
{
	int				length;
	struct NodeEnv	*head;
	struct NodeEnv	*tail;
}				t_env_head;

void	add_token_tail(t_head **head, char *str, int type);
void	free_list(t_head *a);
void	printl(t_head *head);
void	free_list_loop(t_head **a);

#endif