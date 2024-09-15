/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/15 00:14:05 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"


int  pid;

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

void lstclear(t_token **head)
{
	t_token *ne;

	if (!head || !*head)
		return;
	while (*head)
	{
		ne = *head;
		*head = (*head)->next;
		free(ne->str);
		ne->str = NULL;
		free(ne);
		ne = NULL;
	}
	*head = NULL;
}

void	clear_redirections(t_red **head)
{
	t_red	*ne;

	if (!head)
		return ;
	if (*head)
	{
		while (*head)
		{
			ne = *head;
			*head = (*head)->next;
			free(ne->red_file);
			free(ne);
		}
	}
	*head = NULL;
}

void    clear_args_list(t_args **head)
{
	t_args	*ne;

	if (!head)
		return ;
	if (*head)
	{
		while (*head)
		{
			ne = *head;
			*head = (*head)->next;
			free(ne->str);
			free(ne);
		}
	}
	*head = NULL;
}

void	free_all(t_cmd *cmd)
{
	int i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	clear_redirections(&cmd->redirections);
	clear_args_list(&cmd->args_list);
}

void	free_cmd_list(t_cmd **cmds)
{
	t_cmd *tmp;

	if (!cmds)
		return;
	if (*cmds)
	{
		while (*cmds)
		{
			tmp = *cmds;
			*cmds = (*cmds)->next;
			if (tmp->cmd != tmp->path)
				free(tmp->path);
			free_all(tmp);
			free(tmp);
		}
	}
	*cmds = NULL;
}

void leak()
{
	system("leaks ms");
}


void handler(int sign)
{
    (void)sign;
	int save_pid;
	
	save_pid = pid;
    printf("\n");
	if (pid > -1)
	{
		pid = -42;
		kill(save_pid, SIGTERM);
	}
	else if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
   		rl_redisplay();	
	}
}

static void clear_all(t_data *data)
{
    lstclear(&data->head);
    lstclear(&data->pre);
    add_history(data->str);
    free(data->str);
}

int	main(int ac, char **av, char **envp)
{	
	(void)ac;
	(void)av;
    static t_data data;
	struct sigaction sig;

	if (ac > 1)
	    return 1;
	sig.sa_flags = 0;
	sig.sa_handler = &handler;
	init_env(&data.envs, envp, &data.paths);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		pid = -1;
		sigaction(SIGINT, &sig, NULL);
		data.str = readline("msh-0.1$ ");
		if (!data.str)
			ft_exit(&data.cmd);
        if (lexer(data.str, &data.head, data.envs, &data.pre))
        {
            clear_all(&data);
            continue;
        }
        lstclear(&data.head);
		parser(&data.cmd, &data.pre, data.paths, data.envs);
		// traverse_parse_list(data.cmd);
        lstclear(&data.pre);
		add_history(data.str);
		excution(&data.envs, data.cmd, envp, &pid);
		free_cmd_list(&data.cmd);
		free(data.str);
		//system("leaks -q ms");
       // atexit(leak);
	}
}
