/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:51:10 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/18 00:51:10 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stringbuilder.h"

t_stringbuilder	*sb_create(void)
{
	t_stringbuilder	*sb;

	sb = calloc(1, sizeof(t_stringbuilder));
	if (!sb)
		return (NULL);
	sb->str = ft_calloc(1, sizeof(char));
	sb->len = 0;
	return (sb);
}

int	sb_destroy(t_stringbuilder *sb)
{
	free(sb->str);
	sb->str = NULL;
	sb->len = 0;
	free(sb);
	sb = NULL;
	return (0);
}

int	sb_clear(t_stringbuilder *sb)
{
	free(sb->str);
	sb->str = ft_calloc(1, sizeof(char));
	if (!sb->str)
	{
		free(sb);
		return (2);
	}
	sb->len = 0;
	return (0);
}

void	sb_copy_oldstr(t_stringbuilder *sb, char **newstr)
{
	int	i;

	i = 0;
	while (sb->str[i] && i < sb->len)
	{
		(*newstr)[i] = sb->str[i];
		i++;
	}
}
