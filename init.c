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
	t_env	*env;
	t_token	*head;
	t_token	*pre;
	char	*str;

	(void)ac;
	(void)av;
	(void)envp;
	env = NULL;
	init_env(&env, envp);
	head = NULL;
	pre = NULL;
	//env list
	//	traverse_env_list(env);
	while (1)
	{
		str = readline("ms-0.1$ ");
		lexer(str, &head, env, &pre);
		//traverse primary tokens list;
//		traverse_primary_tokens_list(head);
//		printf("\n\n");
		//traverse pre-parse list;
		traverse_primary_tokens_list(pre);
		//		clear the list
//		lstclear(&head, freed);
		lstclear(&pre, freed);
		head = NULL;
		pre = NULL;
//		printf("\n\n\n");
//		system("leaks -q ms");
		add_history(str);
		free(str);
	}
}
