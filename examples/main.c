/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:00:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/19 22:21:16 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_head	*head;
	t_env_head *env_head;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	env_head = (t_env_head *)malloc(sizeof(t_env_head));
	init_envs(&env_head, envp);
	(void) argv;
	while (1)
	{
		head = (t_head *)malloc(sizeof(t_head));
		input = NULL;
		input = readline(MINISHELL);
		if (input)
			add_history(input);
		create_list(&head, input);
		validate(&head, envp);
		printl(head);
		free_list(head);
	}
	return (0);
}
