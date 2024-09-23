/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:37 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int pid;


//to be deleted
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

void handler(int sign)
{
    (void)sign;
	
   printf("\n");
	if (pid != -2)
		pid = -42;
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
   		rl_redisplay();	
	}
}



int	main(int ac, char **av, char **envp)
{	
	(void)av;
    t_data data;

	if (ac > 1)
	    return 1;
	init_all(&data);
	init_env(&data.envs, envp, &data.paths);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	while (1)
	{
        pid = -2;
		data.str = readline("msh-0.1$ ");
		if (!data.str)
			exit(1);
        if (lexer(data.str, &data.head, data.envs, &data.pre))
        {
            clear_all(&data);
            continue;
        }
        lstclear(&data.head);
		parser(&data.cmd, &data.pre, data.paths, data.envs);
        lstclear(&data.pre);
		add_history(data.str);
        excution(&data.envs, data.cmd, &pid);
        free_cmd_list(&data.cmd);
		free(data.str);
	}
	return 0;
}
