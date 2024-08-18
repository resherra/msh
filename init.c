/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/08/16 13:15:44 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"


void	traverse_parse_list(t_cmd *cmd);

int	main(int ac, char **av, char **envp)
{
	t_env	*envs;
	t_token	*head;
	t_token	*pre;
	t_cmd *cmd;
	char	*str;
	char **paths;

	(void)ac;
	(void)av;
	(void)envp;
	envs = NULL;
	init_env(&envs, envp, &paths);
	head = NULL;
	pre = NULL;
	cmd = NULL;
	while (1)
	{
		str = readline("msh-0.1$ ");

		lexer(str, &head, envs, &pre);
		parser(&cmd, pre, paths);
		if (cmd && cmd->cmd && !strcmp("exit", cmd->cmd))
			exit(1);
		excution(&envs, cmd);

		//traverse primary tokens list;
		//		traverse_primary_tokens_list(head);
		//		printf("\n\n");
		//      traverse pre-parse list;
		// traverse_primary_tokens_list(pre);
		//		clear the list
		// traverse_parse_list(cmd);
		// printf("\n\n\n");
		//lstclear(&head, freed);
		//lstclear(&pre, freed);
		head = NULL;
		pre = NULL;
		cmd = NULL;
		add_history(str);
		free(str);
	}
}

