/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:25:15 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/09 03:10:38 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	printl_export(t_env_head *head)
{
	t_env_node	*current;
	int			i;

	i = 0;
	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else if (ft_strlen(current->key) > 0)
			printf("declare -x %s\n", current->key);
		i++;
		current = current->next;
	}
}

void	printl_env(t_env_head *head)
{
	t_env_node	*current;
	int			i;

	i = 0;
	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		if (current->value != NULL)
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
	while (env[i] != NULL)
	{
		str = ft_split(env[i], '=');
		add_env_tail(head, str[0], str[1]);
		free(str);
		i++;
	}
}

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