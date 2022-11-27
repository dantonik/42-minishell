/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:16:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 01:47:55 by dantonik         ###   ########.fr       */
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
	char				*cmnd;
//..........................................
	char				*cmnd_path;
	int					pos;
	int					here_fd[2];
	struct linkedList	*head;
//..........................................
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
	t_bool			echo_n;
	int				length;
	struct Node		*next;
	struct Node		*prev;
}				t_node;

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
	int					length;
	struct linkedList	*thead;
	struct NodeEnv		*head;
	struct NodeEnv		*tail;
}				t_env_head;

typedef struct linkedList
{
	int				length;
// .......................................
	int				temp_fd;
	int				pipe_fd[2];
	int				std_input[2];
	int				std_output[2];
	int				e_s;
	int				exit_cd;
	t_env_head		*envp_ours;
// .......................................
	struct Node		*head;
	struct Node		*current;
	struct Node		*tail;
}				t_head;

typedef struct s_stringbuilder
{
	char	*str;
	int		len;
}	t_stringbuilder;

#endif
