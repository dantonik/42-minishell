#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./string_builder/stringbuilder.h"
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
	char				*exec_cmnd;
	struct LEXER_STRUCT	*next;
	struct LEXER_STRUCT	*prev;
}	t_lexer;

t_lexer	*create_list(char **array);
void	print_list(t_lexer *lexer);
void	free_list(t_lexer *head);
char	*strip_multi_space(char *s);
char	*strip_redirection(char *s);

#endif
