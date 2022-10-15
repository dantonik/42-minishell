#include "inc/minishell.h"

// < redirect input
// > redirect output
// << ???
// >> redirect output in append mode

// echo / echo -n
// cd (with relative and absolute path)
// pwd
// export
// unset
// env
// exit

// handle environment variables
// implement pipes
// $? expands to the exit status of the most recently executed foreground pipeline
// handle ctrl-C/D/\

// bonus
// && and ||
// Wildcards

t_token	*init_token(char *value, int type)
{
	t_token *token;

	token = calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;

	return (token);
}

