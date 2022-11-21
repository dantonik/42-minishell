/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:38:05 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/21 21:44:20 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_token_tail(t_head **head, char *str, int type)
{
	t_node	*new;
	t_node	*current;

	new = (t_node *)malloc(sizeof(t_node));
	(*head)->length++;
	trim_leading_char(str, ' ');
	trim_trailing_char(str, ' ');
	remove_dup_c(str, ' ');
	new->cmnd = str;
	new->type = type;
	new->next = NULL;
	new->cmnd_path = NULL;
	new->head = (*head);
	new->pos = (*head)->length;
	// new->pos = 1;
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
	// {
	// 	new->pos++;
	// 	current = current->next;
	// }
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
		free(temp->cmnd);
		free (temp);
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
		free (temp);
		temp = (*a)->head;
	}
	(*a)->head = NULL;
}
