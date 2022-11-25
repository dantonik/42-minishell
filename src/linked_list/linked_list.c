/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:38:05 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:18:59 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*init_token(void)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->next = NULL;
	new->cmnd_path = NULL;
	return (new);
}

void	add_token_tail(t_head **head, char *str, int type)
{
	t_node	*current;
	t_node	*new;

	(*head)->length++;
	trim_leading_char(str, ' ');
	trim_trailing_char(str, ' ');
	new = init_token();
	new->cmnd = str;
	new->type = type;
	new->head = (*head);
	new->t_builtin = 0;
	new->pos = (*head)->length;
	current = (*head)->head;
	if ((*head)->head == NULL)
	{
		(*head)->head = new;
		(*head)->tail = new;
		new->prev = NULL;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
	(*head)->tail = new;
}

void	free_list(t_head *a)
{
	t_node		*temp;
	t_env_node	*env_temp;

	temp = a->head;
	while (temp != NULL)
	{
		a->head = a->head->next;
		temp->cmnd = NULL;
		temp = NULL;
		temp = a->head;
	}
	free(a);
}

void	printl(t_head *head)
{
	t_node	*current;

	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		printf("___%s___\t[pos:%i]\t[type:%u]\t[builtin:%u]\n", \
			current->cmnd, current->pos, current->type, current->t_builtin);
		current = current->next;
	}
}

void	free_list_loop(t_head **a)
{
	t_node	*temp;

	temp = (*a)->head;
	while (temp != NULL)
	{
		(*a)->head = (*a)->head->next;
		free (temp->cmnd);
		free (temp->cmnd_path);
		free (temp);
		temp = (*a)->head;
	}
	(*a)->head = NULL;
}
