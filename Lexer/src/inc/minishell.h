#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX(a, b)\
	a > b ? a : b

#define MIN(a, b)\
	a < b ? a : b

typedef struct TOKEN_STRUCT
{
	char *value;
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_RBRACE,
		TOKEN_LBRACE,
		TOKEN_COLON,
		TOKEN_SEMI,
		TOKEN_COMMA,
		TOKEN_LT,
		TOKEN_GT,
		TOKEN_RARROW,
		TOKEN_INT,
		TOKEN_SB,
		TOKEN_DB,
		TOKEN_EOF
	} type;
}	t_token;

typedef struct LEXER_STRUCT
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
}	t_lexer;

//--> IO <--//
char	*read_file(const char *filename);

//--> LEXER <--//
t_lexer	*init_lexer(char *src);
void	lexer_advance(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
t_token	*lexer_next_token(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer, int offset);

//--> TOKEN <--//
t_token	*init_token(char *value, int type);

#endif