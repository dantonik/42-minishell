/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:34:25 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:31:23 by dantonik         ###   ########.fr       */
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

t_stringbuilder	*check_var(char *s, t_env_head *head, t_stringbuilder *sb)
{
	int			i;
	char		*var;
	t_env_node	*temp;

	temp = head->head;
	s++;
	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && !ms_ispipe(s[i]) && s[i] != '"')
		i++;
	var = ms_strdup(s, i);
	while (temp->next != NULL)
	{
		if (ms_strcmp_exact(temp->key, var) == 0)
		{
			sb_append_str(sb, temp->value);
			free (var);
			return (sb);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

char	*expander(char *s, t_env_head *head)
{
	int					i;
	int					j;
	char				*new;
	unsigned short int	flags;
	t_stringbuilder		*sb;

	sb = sb_create();
	flags = 0;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !(flags & DQ_FLAG))
			flags ^= SQ_FLAG;
		if (s[i] == '"' && !(flags & SQ_FLAG))
			flags ^= DQ_FLAG;
		if (s[i] == '$' && !(flags & SQ_FLAG))
		{
			check_var(s + i, head, sb);
			while (s[i] != '\0' && s[i] != ' ' && !ms_ispipe(s[i]) \
				&& s[i] != '"')
				i++;
		}
		sb_append_char(sb, s[i]);
		i++;
	}
	sb_append_char(sb, '\0');
	new = sb_get_str(sb);
	sb_destroy(sb);
	if (flags & SQ_FLAG || flags & DQ_FLAG)
	{
		free (new);
		return (NULL);
	}
	return (new);
}
