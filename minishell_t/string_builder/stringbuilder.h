/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:51:16 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/18 00:51:16 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGBUILDER_H
# define STRINGBUILDER_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef struct s_stringbuilder
{
	char	*str;
	int		len;
}	t_stringbuilder;

t_stringbuilder	*sb_create(void);
int				sb_destroy(t_stringbuilder *sb);
int				sb_clear(t_stringbuilder *sb);
void			sb_copy_oldstr(t_stringbuilder *sb, char **newstr);

int				sb_append_char(t_stringbuilder *sb, char c);
int				sb_append_str(t_stringbuilder *sb, char *str);
int				sb_append_strn(t_stringbuilder *sb, char *str, int len);
int				sb_append_int(t_stringbuilder *sb, int nbr);
char			*sb_get_str(t_stringbuilder *sb);

#endif
