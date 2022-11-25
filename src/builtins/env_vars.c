/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:08:48 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:14:29 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_env_head *head)
{
	printl_env(head);
}

void	ft_unset(t_env_head **head, char *s)
{
	t_env_node	*node;
	char		**str;
	int			i;

	if (ft_strlen(s) == 5)
		return ;
	str = ft_split(s, ' ');
	i = 1;
	while (str[i] != NULL)
	{
		node = (*head)->head;
		while (node->next != NULL)
		{
			if (ms_strcmp_exact(node->key, str[i]) == 0)
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
				free(node);
				break ;
			}
			node = node->next;
			if (node->next == NULL && ms_strcmp_exact(node->key, str[i]) == 0)
			{
				node->prev->next = NULL;
				free(node);
				break ;
			}
		}
		i++;
	}
}

int	append_replace(t_env_head **head, char *s, char *s2, int i)
{
	t_env_node	*node;

	node = (*head)->head;
	while (node->next != NULL)
	{
		if (ms_strcmp_exact(node->key, s) == 0)
		{
			node->value = s2;
			return (i);
		}
		node = node->next;
	}
	add_env_tail(head, s, s2);
	return (i);
}

int	check_exp(t_env_head **head, char *cmnd)
{
	t_stringbuilder	*sb;
	t_stringbuilder	*sb2;
	int				i;

	i = 0;
	sb = sb_create();
	while (cmnd[i] && cmnd[i] != '=' && cmnd[i] != ' ')
	{
		sb_append_char(sb, cmnd[i]);
		i++;
	}
	if (cmnd[i] == '\0')
		return (append_replace(head, sb_get_str(sb), NULL, i));
	if (cmnd[i] == ' ')
		return (append_replace(head, sb_get_str(sb), NULL, i + 1));
	if (cmnd[i] == '=' && cmnd[i + 1] == '\0')
		return (append_replace(head, sb_get_str(sb), "\0", i + 1));
	i++;
	sb2 = sb_create();
	while (cmnd[i] && cmnd[i] != ' ')
	{
		sb_append_char(sb2, cmnd[i]);
		i++;
	}
	return (append_replace(head, sb_get_str(sb), sb_get_str(sb2), i));
}

void	ft_export(t_env_head **head, char *cmnd)
{
	int	i;

	if (ms_strcmp_exact("export", cmnd) == 0)
	{
		printl_export(*head);
		return ;
	}
	cmnd += 6;
	if (*cmnd && *cmnd != ' ')
	{
		printf("trash: %s: command not found\n", cmnd - 6);
		return ;
	}
	cmnd++;
	if (*cmnd < 65 || (*cmnd > 90 && *cmnd < 97) || *cmnd > 122)
	{
		printf("trash: export: not a valid identifier\n");
		return ;
	}
	i = 0;
	while (*cmnd)
	{
		i = check_exp(head, cmnd);
		if (i == -1)
		{
			printf("Error\n");
			return ;
		}
		else if (i == 0)
			cmnd ++;
		else
			cmnd += i;
	}
}
