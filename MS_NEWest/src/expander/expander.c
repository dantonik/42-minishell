/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:34:25 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/09 03:31:20 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (0);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*check_var(char *s, t_env_head *head)
{
	int			i;
	char		*var;
	t_env_node	*temp;

	temp = head->head;
	s++;
	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && !ms_ispipe(s[i]))
		i++;
	var = ms_strdup(s, i);
	while (temp->next != NULL)
	{
		if (ms_strcmp_exact(temp->key, var) == 0)
		{
			s = ms_strjoin(s, temp->value);
			free (var);
			return (temp->value);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

char	*expander(char *s, t_env_head *head)
{
	bool	q[2];
	char	*new;
	char	*temp;
	int		i;
	t_stringbuilder	*sb;

	sb = sb_create();
	q[0] = false;
	q[1] = false;
	while (*s != '\0')
	{
		if (*s == '\''&& q[1] == false)
			q[0] = !q[0];
		if (*s == '"' && q[0] == false)
			q[1] = !q[1];
		if (*s == '$' && q[0] == false)
		{
			new = check_var(s, head);
			if (new)
				sb_append_str(sb, new);
			while (*s != '\0' && *s != ' ' && !ms_ispipe(*s))
				s++;
		}
		sb_append_char(sb, *s);
		s++;
	}
	new = sb_get_str(sb);
	sb_destroy(sb);
	return (new);
}