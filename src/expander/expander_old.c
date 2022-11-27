/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:45:07 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/07 20:56:26 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*expander(char *s, t_env_head *head)
// {
// 	int			i;
// 	int			j;
// 	int			exp;
// 	bool		sq[3];
// 	char		*new;zv               
// 	char		*temp;
// 	t_env_node	*cur;

// 	i = 0;
// 	j = 0;
// 	sq[0] = false;
// 	sq[1] = false;
// 	sq[2] = false;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '\'')
// 			sq[0] = !sq[0];
// 		if (s[i] == '"')
// 			sq[1] = !sq[1];
// 		if (sq[0] == false && sq[1] == false && s[i] == '$')
// 		{
// 			i++;
// 			j = 0;
// 			while (s[i + j] != '\0' && s[i + j] != ' ' && !(ms_ispipe(s[i + j])))
// 				j++;
// 			temp = ms_strdup(&s[i], j);
// 			cur = head->head;
// 			while (cur->next != NULL)
// 			{
// 				// if (ms_strcmp_exact(temp, cur->key))
// 				// 	printf("%s\n", cur->key);
// 				cur = cur->next;
// 			}
// 			i--;
// 		}
// 		new[i] = s[i];
// 		i = i + 1;
// 	}
// 	new[i] = '\0';
// 	return (s);
// }

char	*ms_chrjoin(char *s1, char s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL)
	{
		str = (char *)malloc(2 * sizeof(char));
		str[0] = s2;
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = s2;
	str[i + 1] = '\0';
	// free(s1);
	return (str);
}

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
	// free(s1);
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
			return (s + i);
		}
		temp = temp->next;
	}
	free(var);
	return (s);
}

char	*expander(char *s, t_env_head *head)
{
	bool	q[2];
	char	*new;
	char	*temp;
	int		i;

	q[0] = false;
	q[1] = false;
	new = NULL;
	while (*s != '\0')
	{
		if (*s == '\''&& q[1] == false)
			q[0] = !q[0];
		if (*s == '"' && q[0] == false)
			q[1] = !q[1];
		if (*s == '$' && q[0] == false)
		{
			new = check_var(s, head);
			while (*s != '\0' && *s != ' ' && !ms_ispipe(*s))
				s++;
		}
		new = ms_chrjoin(new, *s);
		printf("%c\n", *s);
		s++;
	}
	printf("\n");
	printf("expander: %s\n", new);
	return (new);
}
