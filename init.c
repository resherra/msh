/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/07/13 06:59:20 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*envs;
	t_token	*head;
	t_token	*pre;
	char	*str;

	(void)ac;
	(void)av;
	(void)envp;
	envs = NULL;
	init_env(&envs, envp);
	head = NULL;
	pre = NULL;
	//env list
    //		traverse_env_list(envs);
    //		exit(1);
	while (1)
	{
		str = readline("msh-0.1$ ");

		//test builtins;
		test_builtins(str, envs);
		lexer(str, &head, envs, &pre);
		//traverse primary tokens list;
//		traverse_primary_tokens_list(head);
//		printf("\n\n");
//      traverse pre-parse list;
		traverse_primary_tokens_list(pre);
//		clear the list
		lstclear(&head, freed);
		lstclear(&pre, freed);
		head = NULL;
		pre = NULL;
//		printf("\n\n\n");
		system("leaks -q ms");
		add_history(str);
		free(str);
	}
}


