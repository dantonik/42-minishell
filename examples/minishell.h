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

typedef struct Node
{
	char			*cmnd;
	enum
	{
		CMND,
		STRNG,
		RED_OUT,
		RED_IN,
		HEREDOC,
		APPEND,
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

//-- LINKED_LIST --//
void	add_token_tail(t_head **head, char *str, int type);
void	printl(t_head *head);
void	printl_rev(t_head *head);
void	free_list(t_head *a);

//-- LEXER --//
int		skip_whitespace(char *input);
int		create_token(t_head **head, char *input);
void	create_list(t_head **head, char *input);
void	strip_whitespace(t_node *lexer);

#endif