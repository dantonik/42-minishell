#include "minishell.h"

int	main(void)
{
	char	*input;
	t_lexer	*lexer;

	while (1)
	{
		input = readline(MINISHELL);
		if (input)
			add_history(input);
		lexer = create_list(ft_split(input, '|'));
		print_list(lexer);
		free_list(lexer);
		free(input);
	}
	return (0);
}
