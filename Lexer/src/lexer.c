#include "inc/minishell.h"

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = calloc(1, sizeof(t_lexer));
	lexer->src = src;
	lexer->src_size = strlen(src);
	lexer->i = 0;
	lexer->c = src[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_advance_current(t_lexer *lexer, int type)
{
	char	*value;
	t_token	*token;

	value = calloc(2, sizeof(char));
	value[0] = lexer->c;
	value[1] = '\0';
	token = init_token(value, type);
	lexer_advance(lexer);
	return (token);
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

t_token	*lexer_parse_id(t_lexer *lexer)
{
	char	*value;

	value = calloc(1, sizeof(char));
	while (isalnum(lexer->c))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]){lexer->c, 0});
		lexer_advance(lexer);
	}
	return  (init_token(value, TOKEN_ID));
}

t_token	*lexer_parse_number(t_lexer *lexer)
{
	char	*value;

	value = calloc(1, sizeof(char));
	while (isdigit(lexer->c))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]){lexer->c, 0});
		lexer_advance(lexer);
	}
	return  (init_token(value, TOKEN_INT));
}

char	lexer_peek(t_lexer *lexer, int offset)
{
	return (lexer->src[MIN(lexer->i + offset, lexer->src_size)]);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		skip_whitespace(lexer);
		if (isalnum(lexer->c))
			return (lexer_advance_with(lexer, lexer_parse_id(lexer)));
		
		if (isdigit(lexer->c))
			return (lexer_advance_with(lexer, lexer_parse_number(lexer)));

		switch (lexer->c)
		{
			case '=': return (lexer_advance_current(lexer, TOKEN_EQUALS));
			case '(': return (lexer_advance_current(lexer, TOKEN_LPAREN));
			case ')': return (lexer_advance_current(lexer, TOKEN_RPAREN));
			case '{': return (lexer_advance_current(lexer, TOKEN_LBRACE));
			case '}': return (lexer_advance_current(lexer, TOKEN_RBRACE));
			case ':': return (lexer_advance_current(lexer, TOKEN_COLON));
			case ',': return (lexer_advance_current(lexer, TOKEN_COMMA));
			case '<': return (lexer_advance_current(lexer, TOKEN_LT));
			case '>': return (lexer_advance_current(lexer, TOKEN_GT));
			case '\'': return (lexer_advance_current(lexer, TOKEN_SB));
			case '"': return (lexer_advance_current(lexer, TOKEN_DB));
			case ';': return (lexer_advance_current(lexer, TOKEN_SEMI));
			case '\0': break;
			default: printf("[Lexer]: Unexpected character `%c`\n", lexer->c); exit(1); break;
		}
	}
	return (init_token(0, TOKEN_EOF));
}