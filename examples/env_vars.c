/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:07:35 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/19 21:02:53 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printl_env(t_env_head *head)
{
	t_env_node	*current;
	int		i;

	i = 0;
	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		i++;
		current = current->next;
	}
}

void	add_env_tail(t_env_head **head, char *key, char *value)
{
	t_env_node	*new;
	t_env_node	*current;

	new = (t_env_node *)malloc(sizeof(t_env_node));
	(*head)->length++;
	new->key = key;
	new->value = value;
	new->next = NULL;
	current = (*head)->head;
	if ((*head)->head == NULL)
	{
		(*head)->head = new;
		new->prev = NULL;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
	(*head)->tail = new;
}

void	init_envs(t_env_head **head, char **env)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		printf("%s=%s\n",str[0], str[1]);
		add_env_tail(head, str[0], str[1]);
		free(str);
		i++;
	}
}
