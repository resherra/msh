/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/08/19 04:26:49 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"


void	traverse(t_token *head, t_token *pre, t_cmd *cmd)
{
	(void)head;
	(void)pre;
	(void)cmd;

	//traverse_primary_tokens_list(head);
	// traverse_primary_tokens_list(pre);
	//clear the list
	// traverse_parse_list(cmd);
	// printf("\n\n\n");
}


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*str;
	char **paths;
	t_env	*envs;
	t_token	*head;
	t_token	*pre;
	t_cmd *cmd;
	envs = NULL;
	head = NULL;
	pre = NULL;
	cmd = NULL;
	paths = NULL;
	init_env(&envs, envp, &paths);
	while (1)
	{
		str = readline("msh-0.1$ ");
		lexer(str, &head, envs, &pre);
		parser(&cmd, &pre, paths);
		excution(&envs, cmd);
		//traverse_parse_list(cmd);
		traverse(head, pre, cmd);
		cmd = NULL;
		add_history(str);
		free(str);
	}
}

