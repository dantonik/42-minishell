/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:12:13 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/28 04:42:20 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_arr_size(char **arr)
{
	int	res;

	if (!arr)
		return (0);
	res = 0;
	while (arr[res])
		res++;
	return (res);
}

static bool	check_valid_arg(char *arg)
{
	if (!*arg || (*arg != '+' && *arg != '-' && !ft_isdigit(*arg)))
		return (false);
	arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

int	exit_code(t_node *temp)
{
	char	**cmnd;
	int		arr_size;
	int		num_val;

	cmnd = ft_split(temp->cmnd, ' ');
	arr_size = get_arr_size(cmnd);
	if (arr_size > 2)
	{
		my_free(cmnd);
		return (printf("exit\ntrash: exit: too many arguments\n"), 1);
	}
	if (arr_size > 1)
	{
		if (cmnd[1] && check_valid_arg(cmnd[1]))
			return (num_val = ft_atoi(cmnd[1]) % 256, my_free(cmnd), num_val);
		else
		{
			printf("exit\ntrash: exit: %s: numeric argument required\n", cmnd[1]);
			return (my_free(cmnd), 255);
		}
	}
	else
		return (my_free(cmnd), 0);
}
