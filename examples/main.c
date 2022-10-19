/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:00:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/20 00:38:37 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list_loop(t_head **a)
{
	t_node	*temp;

	temp = (*a)->head;
	while (temp != NULL)
	{
		(*a)->head = (*a)->head->next;
		free (temp);
		temp = (*a)->head;
	}
	(*a)->head = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_head		*head;
	t_env_head	*env_head;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	head = (t_head *)malloc(sizeof(t_head));
	env_head = (t_env_head *)malloc(sizeof(t_env_head));
	init_envs(&env_head, envp);
	(void) argv;
	while (1)
	{
		input = NULL;
		input = readline(MINISHELL);
		if (input)
			add_history(input);
		create_list(&head, input);
		validate(head, env_head);
		printl(head);
		free_list_loop(&head);
	}
	free(head);
	return (0);
}
