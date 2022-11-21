/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/21 22:03:59 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
	{
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "  \b\b", 4);
}

static int	check_empty_input(char *input)
{
	int	i;

	i = 0;
	while (1)
	{
		if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
			i++;
		else
			break ;
	}
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

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
	if (head == NULL)
		exit(1);
	(void) argv;
	head->std_input[1] = dup(0);
	head->std_output[1] = dup(1);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		input = NULL;
		input = readline(MINISHELL);
		if (check_empty_input(input))
			continue ;
		else
			add_history(input);
		input = expander(input, env_head);
		head->length = 0;
		head->temp_fd = -1;
		head->envp_og = envp;
		create_list(&head, input);
		check_builtins(head);
		main_loop(head, env_head);
		free(input);
		// printl(head);
		free_list_loop(&head);
	}
	close(head->std_input[1]);
	close(head->std_output[1]);
	free(head);
	return (0);
}
