#include "minishell.h"

void	free_list(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		free(current->cmnd);
		free(current->exec_cmnd);
		free(current);
		current = current->next;
	}
}

void	print_list(t_lexer *lexer)
{
	while (lexer)
	{
		printf("%s\n", lexer->cmnd);
		printf("%s", lexer->exec_cmnd);
		lexer = lexer->next;
		printf("\n");
	}
}

static t_lexer	*create_node(char *cmnd)
{
	t_lexer	*new;

	if (!cmnd)
		return (NULL);
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	cmnd = strip_multi_space(cmnd);
	new->cmnd = ft_strtrim(cmnd, " ");
	new->exec_cmnd = strip_redirection(new->cmnd);
	free(cmnd);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*create_list(char **array)
{
	t_lexer	*head;
	t_lexer	*temp;
	int		i;

	i = 0;
	head = create_node(array[i]);
	if (!head)
		return (NULL);
	temp = head;
	i++;
	while (array[i])
	{
		temp->next = create_node(array[i]);
		if (!temp->next)
			return (NULL);
		temp->next->prev = temp;
		temp = temp->next;
		i++;
	}
	return (head);
}
