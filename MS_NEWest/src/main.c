/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/02 14:57:50 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_head		*head;
	t_env_head	*env_head;

	if (argc != 1)
	{
		printf("trash: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	if (envp[0] == NULL)
	{
		printf("trash: send the environment please!\n");
		return (EXIT_FAILURE);
	}
	env_head = (t_env_head *)malloc(sizeof(t_env_head));
	init_envs(&env_head, envp);
	// printl_env(env_head);
	head = (t_head *)malloc(sizeof(t_head));
	(void) argv;
	while (1)
	{
		input = NULL;
		input = readline(MINISHELL);
		create_list(&head, input);
		check_builtins(head);
		free(input);
		printl(head);
		free_list_loop(&head);
	}
	free(head);
	return (0);
}
