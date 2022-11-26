/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:08:48 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/26 01:01:31 by cboubour         ###   ########.fr       */
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
				if (node == (*head)->head)
				{
					(*head)->head = node->next;
					node->next->prev = node->prev;
					my_free(str);
					free(node->key);
					free(node->value);
					free(node);
					return ;
				}
				node->prev->next = node->next;
				node->next->prev = node->prev;
				my_free(str);
				free(node->key);
				free(node->value);
				free(node);
				return ;
			}
			node = node->next;
			if (node->next == NULL && ms_strcmp_exact(node->key, str[i]) == 0)
			{
				node->prev->next = NULL;
				my_free(str);
				free(node->key);
				free(node->value);
				free(node);
				return ;
			}
		}
		i++;
	}
	my_free(str);
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
	char			*c;

	i = 0;
	sb = sb_create();
	while (cmnd[i] && cmnd[i] != '=' && cmnd[i] != ' ')
	{
		sb_append_char(sb, cmnd[i]);
		i++;
	}
	if (cmnd[i] == '\0')
	{
		i = append_replace(head, sb_get_str(sb), NULL, i);
		sb_destroy(sb);
		return (i);
	}
	if (cmnd[i] == ' ')
	{
		i = append_replace(head, sb_get_str(sb), NULL, i + 1);
		sb_destroy(sb);
		return (i);
	}
	if (cmnd[i] == '=' && cmnd[i + 1] == '\0')
	{
		c = (char *)malloc(sizeof(char));
		*c = '\0';
		i = append_replace(head, sb_get_str(sb), c, i + 1);
		sb_destroy(sb);
		return (i);
	}
	i++;
	sb2 = sb_create();
	while (cmnd[i] && cmnd[i] != ' ')
	{
		sb_append_char(sb2, cmnd[i]);
		i++;
	}
	i = append_replace(head, sb_get_str(sb), sb_get_str(sb2), i);
	sb_destroy(sb);
	sb_destroy(sb2);
	return (i);
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
