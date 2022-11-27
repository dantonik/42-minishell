/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:34:25 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 02:19:09 by dantonik         ###   ########.fr       */
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
	char		*c;

	temp = head->head;
	s++;
	i = 0;
	if (s[0] == '?' && s[1] == '\0' || (s[1] && (s[1] == ' '
				|| s[1] == '/' || s[1] == '\0')))
		return (c = ft_itoa(head->thead->e_s), sb_append_str(sb, c), \
				free (c), sb);
	while (s[i] != '\0' && s[i] != ' ' && !ms_ispipe(s[i]) && s[i] != '"')
		i++;
	var = ms_strdup(s, i);
	while (temp->next != NULL)
	{
		if (ms_strcmp_exact(temp->key, var) == 0)
			return (sb_append_str(sb, temp->value), free (var), sb);
		temp = temp->next;
	}
	return (free(var), NULL);
}

t_stringbuilder	*h(char *s, t_env_head *h, t_stringbuilder *sb, unsigned int *f)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !((*f) & DQ_FLAG))
			(*f) ^= SQ_FLAG;
		if (s[i] == '"' && !((*f) & SQ_FLAG))
			(*f) ^= DQ_FLAG;
		if (s[i] == '$' && !((*f) & SQ_FLAG))
		{
			check_var(s + i, h, sb);
			while (s[i] != '\0' && s[i] != ' ' && !ms_ispipe(s[i]) \
				&& s[i] != '"')
				i++;
			continue ;
		}
		sb_append_char(sb, s[i]);
		i++;
	}
	return (sb);
}

char	*expander(char *s, t_env_head *head)
{
	int					i;
	int					j;
	char				*new;
	unsigned int		flags;
	t_stringbuilder		*sb;

	flags = 0;
	sb = sb_create();
	sb = h(s, head, sb, &flags);
	sb_append_char(sb, '\0');
	new = sb_get_str(sb);
	sb_destroy(sb);
	if (flags & SQ_FLAG || flags & DQ_FLAG)
	{
		free (new);
		return (NULL);
	}
	remove_dup_c(new, ' ');
	free (s);
	return (new);
}
