/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:12:17 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 03:12:51 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_head	*init_head(char **argv)
{
	t_head	*head;

	(void) argv;
	return (head = (t_head *)ft_calloc(1, sizeof(t_head)), \
	head->std_input[1] = dup(0), head->std_output[1] = dup(1), head);
}
