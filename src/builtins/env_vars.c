/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:08:48 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 03:00:03 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_env_head *head, t_head *thead)
{
	thead->head = 0;
	printl_env(head);
}

static void	f(t_env_node *node, char **str)
{
	my_free(str);
	free(node->key);
	free(node->value);
	free(node);
}

int	ft_unset(t_env_head **head, char *s, int i)
{
	t_env_node	*node;
	char		**str;

	if (ft_strlen(s) == 5)
		return (0);
	str = ft_split(s, ' ');
	while (str[i] != NULL)
	{
		node = (*head)->head;
		while (node->next != NULL)
		{
			if (ms_strcmp_exact(node->key, str[i]) == 0)
			{
				if (node == (*head)->head)
					return ((*head)->head = node->next, node->next->prev = \
					node->prev, f(node, str), 0);
				return (node->prev->next = node->next, node->next->prev = \
				node->prev, f(node, str), 0);
			}
			node = node->next;
			if (node->next == NULL && ms_strcmp_exact(node->key, str[i++]) == 0)
				return (node->prev->next = NULL, f(node, str), 0);
		}
	}
	return (my_free(str), 0);
}
