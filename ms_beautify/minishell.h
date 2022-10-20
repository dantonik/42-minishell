#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// # include <stdlib.h>
// # include <signal.h>
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <termios.h>
// # include <sys/ioctl.h>

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

//-- LINKED_LIST --//
void	add_token_tail(t_head **head, char *str, int type);
void	printl(t_head *head);
void	printl_rev(t_head *head);
void	free_list(t_head *a);

//-- LEXER --//
int		skip_whitespace(char *input);
int		create_token(t_head **head, char *input);
void	create_list(t_head **head, char *input);

//-- ENV_VARS --//
void	printl_env(t_env_head *head);
void	add_env_tail(t_env_head **head, char *key, char *value);
void	init_envs(t_env_head **head, char **env);
void	free_env_list(t_env_head *a);

//-- BUILTINS --//
void	check_builtins(t_head **h);

#endif