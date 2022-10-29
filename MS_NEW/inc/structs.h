/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:16:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/26 05:35:56 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct Node
{
	char			*cmnd;
	t_bool			invalid;
	int				here_fd[2];
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

#endif
