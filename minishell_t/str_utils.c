#include "minishell.h"

char	*strip_multi_space(char *s)
{
	int			ij[2];
	int			count;
	char		*new;

	ij[0] = -1;
	ij[1] = 0;
	count = 0;
	while (s[++ij[0]] != '\0')
	{
		if (s[ij[0]] == ' ' || s[ij[0]] == '\t')
			count++;
		if (s[ij[0]] != ' ' && s[ij[0]] != '\t')
		{
			if (count >= 1)
			{
				count = 0;
				s[ij[1]++] = ' ';
			}
			s[ij[1]++] = s[ij[0]];
		}
	}
	s[ij[1]] = '\0';
	new = ft_strdup(s);
	free(s);
	return (new);
}

char	*strip_redirection(char *s)
{
	t_stringbuilder	*str;
	char			*res;

	str = sb_create();
	while (*s != '\0')
	{
		if (*s == '<' || *s == '>')
		{
			s++;
			if (*s == '<' || *s == '>')
				s++;
			if (*s == ' ')
				s++;
			while (*s != '\0' && *s != ' ')
				s++;
		}
		else
			sb_append_char(str, *s);
		if (*s != '\0')
			s++;
	}
	res = sb_get_str(str);
	sb_destroy(str);
	return (res);
}
