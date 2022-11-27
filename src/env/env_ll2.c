/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ll2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:04:16 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 03:04:49 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env_list(t_env_head *a)
{
	t_env_node	*temp;

	temp = a->head;
	while (temp != NULL)
	{
		a->head = a->head->next;
		free(temp->key);
		free(temp->value);
		free (temp);
		temp = a->head;
	}
	free(a);
}

void	free_list_env(t_env_head **a)
{
	t_env_node	*temp;

	temp = (*a)->head;
	while (temp != NULL)
	{
		(*a)->head = (*a)->head->next;
		free (temp->key);
		free (temp->value);
		free (temp);
		temp = (*a)->head;
	}
	(*a)->head = NULL;
}
