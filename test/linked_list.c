/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:38:05 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/28 00:22:20 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_tail(t_head **head, char *str, int type)
{
	t_node	*new;
	t_node	*current;

	new = (t_node *)malloc(sizeof(t_node));
	(*head)->length++;
	new->cmnd = ft_strtrim(str, " ");
	new->type = type;
	new->next = NULL;
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
		printf("___%s___\t[type:%u]\t[builtin:%u]\n", current->cmnd, current->type, current->t_builtin);
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
