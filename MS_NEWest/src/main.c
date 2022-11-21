/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/10 20:37:21 by dantonik         ###   ########.fr       */
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
	env_head = (t_env_head *)ft_calloc(1, sizeof(t_env_head));
	init_envs(&env_head, envp);
	// printl_env(env_head);
	head = (t_head *)ft_calloc(1, sizeof(t_head));
	(void) argv;
	while (1)
	{
		input = NULL;
		input = readline(MINISHELL);
		input = expander(input, env_head);
		create_list(&head, input);
		check_builtins(head);
		if (head->head->t_builtin == T_EXPORT)
			ft_export(&env_head, head->head->cmnd);
		if (head->head->t_builtin == T_ENV)
			ft_env(env_head);
		if (head->head->t_builtin == T_UNSET)
			ft_unset(&env_head, head->head->cmnd);
		if (head->head->t_builtin == T_ECHO)
			ft_echo(head->head, head->head->cmnd);
		free(input);
		// printl(head);
		free_list_loop(&head);
	}
	free(head);
	return (0);
}
