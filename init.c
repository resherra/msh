/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/01 18:20:57 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"


int pid;

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

typedef struct s_data
{
    t_env	*envs;
    t_token	*head;
    t_token	*pre;
    t_cmd *cmd;
    char **paths;
    char	*str;
} t_data;

//#include "/Users/recherra/goinfre/homebrew/Cellar/readline/8.2.13/include/readline/history.h"
//#include "/Users/recherra/goinfre/homebrew/Cellar/readline/8.2.13/include/readline/readline.h"

void handler(int sign)
{
    (void)sign;
//	printf("--->%i\n", pid);
	 if (pid == -1)
	 {
		//printf("pa. = %i\n", pid);
		kill(pid, SIGTERM);
	 }
	 else
	 {
		rl_replace_line("", 0);
		rl_on_new_line();
   		rl_redisplay();	
	 }
}

int	main(int ac, char **av, char **envp)
{	
	(void)ac;
	(void)av;
    static t_data data;
	struct sigaction sig;

	sig.sa_flags = 0;
	sig.sa_handler = &handler;
	
	init_env(&data.envs, envp, &data.paths);
	
	while (1)
	{
		pid = -1;
		sigaction(SIGINT, &sig, NULL);
		data.str = readline("msh-0.1$ ");
		if (data.str == NULL)
			ft_exit(&data.cmd) ;
		if (lexer(data.str, &data.head, data.envs, &data.pre))
        {
            lstclear(&data.head);
            lstclear(&data.pre);
            free(data.str);
            continue;
        }
		lstclear(&data.head);
		if (parser(&data.cmd, &data.pre, data.paths, data.envs))
        {
            lstclear(&data.pre);
            free_cmd_list(&data.cmd);
            free(data.str);
            continue;
        }
		lstclear(&data.pre);
		excution(&data.envs, data.cmd, envp, &pid);
		free_cmd_list(&data.cmd);
		add_history(data.str);
		free(data.str);
       // atexit(leak);
	}
}
