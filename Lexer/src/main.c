#include "inc/minishell.h"

void	compile_input(char *src)
{
	t_lexer *lexer;
	t_token *token;

	lexer = init_lexer(src);
	while ((token = lexer_next_token(lexer))->type != TOKEN_EOF)
	{
		printf("TOK(%s) (%d)\n", token->value, token->type);
	}
	printf("TOK(%s) (%d)\n", token->value, token->type);
}

int	main(int argc, char *argv[])
{
	char	*src;
	if (argc < 2)
	{
		printf("Please specify input file.\n");
		return (1);
	}
	src = read_file(argv[1]);
	compile_input(src);
	free(src);
	return (0);
}