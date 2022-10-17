#include "minishell.h"

void	strip_whitespace(t_lexer *lexer)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (lexer->cmnd[i] == 13 || lexer->cmnd[i] == 10 || lexer->cmnd[i] == ' ' || lexer->cmnd[i] == '\t')
		i++;
	j = i;
	while (lexer->cmnd[j] != '\0')
		j++;
	while (lexer->cmnd[--j] == 13 || lexer->cmnd[j] == 10 || lexer->cmnd[j] == ' ' || lexer->cmnd[j] == '\t')
		;
	k = 0;
	str = (char *)malloc(sizeof(char) * (j - i));
	while (i <= j)
		str[k++] = lexer->cmnd[i++];
	str[k] = '\0';
	lexer->cmnd = str;
}

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
