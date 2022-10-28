#include "minishell.h"

void	remove_dup_c(char *s, char c)
{
	int		i;
	int		j;
	bool	sq;
	bool	dq;

	i = 0;
	j = 0;
	sq = false;
	dq = false;
	while (s[i + j] != '\0')
	{
		if (s[i + j] == '\'')
			sq = !sq;
		if (s[i + j] == '"')
			dq = !dq;
		if (sq == false && dq == false && s[i + j] == c && s[i + j + 1] == c)
		{
			j++;
			continue;
		}
		else
			s[i] = s[i + j];
		i++;
	}
	s[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;

	if (!set || !s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	count = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[count]))
		count--;
	return (ft_substr(s1, 0, count + 1));
}

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

void	trim_leading_char(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] == c)
		i++;
	if (i != 0)
	{
		j = 0;
		while (s[j + i] != '\0')
		{
			s[j] = s[j + i];
			j++;
		}
		s[j] = '\0';
	}
}

void	trim_trailing_char(char *s, char c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (s[i] == c)
			i--;
		else
			break ;
	}
	s[i + 1] = '\0';
}

int	ms_ispipe(int x)
{
	return (x == '<' || x == '|' || x == '>');
}

int	ms_iswhite(int x)
{
	return (x == ' ' || x == '\t' || x == '\r' || x == '\n' || x == '\f');
}

int	skip_whitespace(char *input)
{
	int	i;

	i = 0;
	while (ms_iswhite(input[i]))
		i++;
	return (i);
}

// void	input_token_data(t_token *tokens, char **line, int i)
// {
// 	if (ft_strcmp(line[i], "|") == 0)
// 	{
// 		tokens->type = PIPE;
// 		tokens->value = ft_strdup(line[i]);
// 	}
// 	else if (ft_strcmp(line[i], "<") == 0)
// 	{
// 		tokens->type = INPUT;
// 		tokens->value = ft_strdup(line[i]);
// 	}
// 	else if (ft_strcmp(line[i], ">") == 0)
// 	{
// 		tokens->type = TRUNC;
// 		tokens->value = ft_strdup(line[i]);
// 	}
// 	else if (ft_strcmp(line[i], ">>") == 0)
// 	{
// 		tokens->type = APPEND;
// 		tokens->value = ft_strdup(line[i]);
// 	}
// 	else if (ft_strcmp(line[i], "<<") == 0)
// 	{
// 		tokens->type = HEREDOC;
// 		tokens->value = ft_strdup(line[i]);
// 	}
// }

void	create_list(char *s)
{
	int	i;

	trim_leading_char(s, ' ');
	trim_trailing_char(s, ' ');
	i = 0;
	while (s[i] != '\0')
	{
		// create_token()
		i++;
	}
}

int	main(void)
{
	char str[] = "   <<     test     |     tst     >     t  ";
	t_head		*head;
	int			i;
	remove_dup_c(str, ' ');

	// create_list(str);
	printf("%s\n", str);
}