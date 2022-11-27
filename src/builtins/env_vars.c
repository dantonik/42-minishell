/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:08:48 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 06:02:08 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_unset(char **str, t_env_node *node)
{
	my_free(str);
	free(node->key);
	free(node->value);
	free(node);
}

void	ft_unset(t_env_head **head, char *s, int i)
{
	t_env_node	*node;
	char		**str;

	if (ft_strlen(s) == 5)
		return ;
	str = ft_split(s, ' ');
	while (str[i] != NULL)
	{
		node = (*head)->head;
		while (node->next != NULL)
		{
			if (ms_strcmp_exact(node->key, str[i]) == 0)
			{
				if (node == (*head)->head)
					return ((*head)->head = node->next, \
					node->next->prev = node->prev, free_unset(str, node));
				return (node->prev->next = node->next, \
				node->next->prev = node->prev, free_unset(str, node));
			}
			node = node->next;
			if (node->next == NULL && ms_strcmp_exact(node->key, str[i++]) == 0)
				return (node->prev->next = NULL, free_unset(str, node));
		}
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

int	check_exp(t_env_head **head, char *cmnd, int i)
{
	t_stringbuilder	*sb;
	t_stringbuilder	*sb2;
	char			*c;

	sb = sb_create();
	while (cmnd[i] && cmnd[i] != '=' && cmnd[i] != ' ')
		sb_append_char(sb, cmnd[i++]);
	if (cmnd[i] == '\0')
		return (i = append_replace(head, \
		sb_get_str(sb), NULL, i), sb_destroy(sb), i);
	if (cmnd[i] == ' ')
		return (i = append_replace(head, \
		sb_get_str(sb), NULL, i + 1), sb_destroy(sb), i);
	if (cmnd[i] == '=' && cmnd[i + 1] == '\0')
		return (c = (char *)malloc(sizeof(char)), \
		*c = '\0', i = append_replace(head, \
		sb_get_str(sb), c, i + 1), sb_destroy(sb), i);
	i++;
	sb2 = sb_create();
	while (cmnd[i] && cmnd[i] != ' ')
		sb_append_char(sb2, cmnd[i++]);
	return (i = append_replace(head, sb_get_str(sb), \
	sb_get_str(sb2), i), sb_destroy(sb), sb_destroy(sb2), i);
}

void	ft_export(t_env_head **head, char *cmnd)
{
	int	i;

	if (ms_strcmp_exact("export", cmnd) == 0)
		return ((void)printl_export(*head));
	cmnd += 6;
	if (*cmnd && *cmnd != ' ')
		return ((void)printf("trash: %s: command not found\n", cmnd - 6));
	cmnd++;
	if (*cmnd < 65 || (*cmnd > 90 && *cmnd < 97) || *cmnd > 122)
		return ((void)printf("trash: export: not a valid identifier\n"));
	i = 0;
	while (*cmnd)
	{
		i = check_exp(head, cmnd, 0);
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
