/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:12:13 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/26 22:32:42 by cboubour         ###   ########.fr       */
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
	if (!*arg || (*arg != '+' && *arg != '-' && !ft_is_digit(*arg)))
		return (false);
	arg++;
	while (*arg)
	{
		if (!ft_is_digit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

int	exit_code(_node *temp)
{
	char	**cmnd;
	int		arr_size;

	cmnd = ft_split(temp->cmnd, ' ');
	arr_size = get_arr_size(cmnd);
	if (arr_size > 0)
	{
		if (cmnd[1] && check_valid_arg(cmnd[1]))
			return (ft_atoi(cmnd[1]));
		else
			printf("exit\ntrash: exit: %s: numeric argument required" ,);
	}
	else
		mini->ret = 0;
	if (arr_size > 2)
		return (printf("exit\ntrash: exit: too many arguments\n"), 1);
}

void	ft_exit(t_table *table)
{
	char	**command;

	command = ft_split(temp->cmnd, ' ');
	if (get_arr_size(command) > 0)
	{
		if (ft_is_alpha(**table->cmd_arr)
			|| get_arr_size(table->cmd_arr) == 1)
		{
			if (check_valid_arg(*table->cmd_arr))
				g_exit_status = ft_atoi(*table->cmd_arr);
			else
				g_exit_status = exit_error(*table->cmd_arr, 255);
			free_table(&table);
			valid_exit();
		}
		g_exit_status = error_msg("exit: too many arguments", FAIL);
		return ;
	}
	g_exit_status = SUCCESS;
	free_table(&table);
	valid_exit();
}
