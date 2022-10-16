#include "minishell.h"

void	free_list(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		free(current);
		current = current->next;
	}
}

void	print_list(t_lexer *lexer)
{
	while (lexer)
	{
		printf("%s", lexer->cmnd);
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
	new->cmnd = ft_strtrim(cmnd, " ");
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
