/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:34:21 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/23 20:01:04 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_copy_words(char **words, char const *s, char c)
{
	size_t	i;
	size_t	k;
	int		n_word;

	i = 0;
	n_word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		k = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			k++;
		}
		if (k > 0)
		{
			words[n_word] = ft_substr(s, i - k, k);
			n_word++;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	// int		i;

	if (!s)
		return (NULL);
	// i = 0;
	// while (s[i] && s[i] == ' ')
	// {
	// 	i++;
	// }
	// if (s[i] == '\0')
	// {
	// 	printf("Error\n");
	// 	return (NULL);
	// }
	words = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	return (ft_copy_words(words, s, c));
}
