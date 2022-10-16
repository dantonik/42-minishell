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

typedef struct LEXER_STRUCT
{
	char				*cmnd;
	struct LEXER_STRUCT	*next;
	struct LEXER_STRUCT	*prev;
}	t_lexer;

typedef struct HIST_STRUCT
{
	int					nbr;
	char				*cmd_line;
	struct HIST_STRUCT	*next;
	struct HIST_STRUCT	*prev;
}	t_hist;

t_lexer	*create_list(char **array);
void	print_list(t_lexer *lexer);
void	free_list(t_lexer *head);
void	put_input_in_history(char *input_line);

#endif
