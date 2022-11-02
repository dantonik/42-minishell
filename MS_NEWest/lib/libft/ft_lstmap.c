/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:42:34 by dantonik          #+#    #+#             */
/*   Updated: 2022/04/20 16:34:36 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*iterate;
	t_list	*new;
	t_list	*new_list;

	if (!lst || !f)
		return (NULL);
	iterate = lst;
	new_list = NULL;
	while (iterate)
	{
		new = ft_lstnew(f(iterate->content));
		if (!new)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new);
		iterate = iterate->next;
	}
	return (new_list);
}
