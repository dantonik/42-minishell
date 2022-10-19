/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:00:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/19 02:01:05 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_head	*head;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	(void) argv;
	while (1)
	{
		head = (t_head *)malloc(sizeof(t_head));
		input = NULL;
		input = readline(MINISHELL);
		if (input)
			add_history(input);
		create_list(&head, input);
		printl(head);
		free_list(head);
	}
	return (0);
}
