/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:00:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/20 16:01:56 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_start()
{
printf("\033[1;36m\n\033[0;36m");
printf("    .                               oooo             .oooo.         .oooo.   \n");
printf("  .o8                               `888           .dP\"\"Y88b      .dP\"\"Y88b  \n");
printf(".o888oo oooo d8b  .oooo.    .oooo.o  888 .oo.            ]8P'           ]8P' \n");
printf("  888   `888\"\"8P `P  )88b  d88(  \"8  888P\"Y88b       <88b.           .d8P'  \n");
printf("  888    888      .oP\"888  `\"Y88b.   888   888          `88b.       .dP'     \n");
printf("  888 .  888     d8(  888  o.  )88b  888   888     o.   .88P  .o. .oP     .o \n");
printf("  \"888\" d888b    `Y888\"\"8o 8\"\"888P' o888o o888o    `8bd88P'   Y8P 8888888888 \n");
printf("                                                                             \n");
printf("\n");
}

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

void	edge_cases(t_head *head, t_env_head *env_head)
{
	if (head->head->type == PIPE || head->tail->type == PIPE)
		printf("trash: syntax error near unexpected token `|'\n");
}


// void	ft_sig_handler(int signal)
// {
// 	(void) signal;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_head	*head;
	t_env_head *env_head;

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
	print_start();
	// signal(SIGINT, ft_sig_handler);
	// signal(SIGQUIT, SIG_IGN);
	env_head = (t_env_head *)malloc(sizeof(t_env_head));
	init_envs(&env_head, envp);
	// printl_env(env_head);
	head = (t_head *)malloc(sizeof(t_head));
	(void) argv;
	while (1)
	{
		input = NULL;
		input = readline(MINISHELL);
		if (input)
			add_history(input);
		create_list(&head, input);
		if (head->head != NULL && head->tail != NULL)
			edge_cases(head, env_head);
		check_builtins(&head);
		printl(head);
		free_list_loop(&head);
	}
	free(head);
	return (0);
}