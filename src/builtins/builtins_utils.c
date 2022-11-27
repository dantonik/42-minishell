/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 02:21:51 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 03:15:34 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in(t_env_head *envp, t_node *current, t_bool forked)
{
	if (current->t_builtin == T_ECHO)
		return (ft_echo(current->head, current, current->cmnd), 0);
	if (current->t_builtin == T_CD)
		return (current->head->e_s = 0, ft_cd(current), 0);
	if (current->t_builtin == T_PWD)
		return (current->head->e_s = 0, ft_pwd(current->head), 0);
	if (current->t_builtin == T_EXPORT)
		return (current->head->e_s = 0, \
		ft_export(&envp, current->cmnd, current->head), 0);
	if (current->t_builtin == T_UNSET)
		return (current->head->e_s = 0, ft_unset(&envp, current->cmnd, 1), 0);
	if (current->t_builtin == T_ENV)
		return (current->head->e_s = 0, ft_env(envp, current->head), 0);
	if (current->t_builtin == T_EXIT)
		return (current->head->e_s = 0, dprintf(2, "exit()"), 0);
	if (forked)
		exit(EXIT_SUCCESS);
	else
		return (0);
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

static int	check_exp(t_env_head **head, char *cmnd, int i)
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

int	ft_export(t_env_head **head, char *cmnd, t_head *thead)
{
	int	i;

	if (ms_strcmp_exact("export", cmnd) == 0)
		return (thead->e_s = 0, printl_export(*head), 0);
	cmnd += 6;
	if (*cmnd && *cmnd != ' ')
		return (thead->e_s = 1, \
		printf("trash: %s: command not found\n", cmnd - 6));
	cmnd++;
	if (*cmnd < 65 || (*cmnd > 90 && *cmnd < 97) || *cmnd > 122)
		return (thead->e_s = 1, \
		printf("trash: export: not a valid identifier\n"));
	i = 0;
	while (*cmnd)
	{
		i = check_exp(head, cmnd, i);
		if (i == -1)
			return (thead->e_s = 1, printf("Error\n"));
		else if (i == 0)
			cmnd ++;
		else
			cmnd += i;
	}
	thead->e_s = 0;
	return (0);
}
