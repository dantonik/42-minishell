#include "minishell.h"

static void	history_go_to_last(t_hist **lst)
{
	if (!*lst)
		return ;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
}

static void	history_lstadd_back(t_hist *last, t_hist *new)
{
	if (!new)
		return ;
	if (!last)
	{
		new->nbr = 1;
		g_msh.history = new;
		g_msh.hist_curr = new;
		return ;
	}
	history_go_to_last(&last);
	new->nbr = last->nbr + 1;
	last->next = new;
	new->prev = last;
	g_msh.hist_curr = new;
}

void	put_input_in_history(char *input_line)
{
	t_hist	*new;

	history_go_to_last(&g_msh.hist_curr);
	new = ft_calloc(1, sizeof(t_hist));
	new->cmd_line = ft_strdup(input_line);
	history_lstadd_back(g_msh.hist_curr, new);
}

void	erase_history(t_hist **lst)
{
	t_hist	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		free((*lst)->cmd_line);
		free(*lst);
		*lst = aux;
	}
	*lst = NULL;
}
