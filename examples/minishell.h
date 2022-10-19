#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "\033[1;93mminishell % \033[0;39m"

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
char	*strip_multi_space(char *s);

//-- ENV_VARS --//
void	printl_env(t_env_head *head);
void	add_env_tail(t_env_head **head, char *key, char *value);
void	init_envs(t_env_head **head, char **env);

void	validate(t_head *head, t_env_head *envp);

#endif
