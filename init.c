/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/20 13:11:28 by apple            ###   ########.fr       */
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

static void clear_all(t_data *data)
{
    lstclear(&data->head);
    lstclear(&data->pre);
    add_history(data->str);
    free(data->str);
}


char **lst_to_envp(t_env *envs)
{
    int i = 0;
    t_env *curr = envs;
    while (curr)
    {
        i++;
        curr = curr->next;
    }
    char **res = malloc(sizeof(char *) * (i + 1));
    if (!res)
        exit(1);

    i = 0;
    t_env *new = envs;
    new = new->next;
    while (new)
    {
        if (new->in_export == FALSE)
        {
            char *trimmed_value = ft_strtrim(new->value, "\x03");
            char *full_key = ft_strjoin(new->key, "=");
            res[i++] = ft_strjoin(full_key, trimmed_value);
            free(trimmed_value);
            free(full_key);
        }
        new = new->next;
    }
    res[i] = 0;
    return res;
}

int	main(int ac, char **av, char **envp)
{	
	(void)ac;
	(void)av;
    static t_data data;

	if (ac > 1)
	    return 1;

	init_env(&data.envs, envp, &data.paths);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	while (1)
	{
		pid = -2;
		data.str = readline("msh-0.1$ ");
		if (!data.str)
		{
			printf("exit\n");
			exit(1);
		}
        if (lexer(data.str, &data.head, data.envs, &data.pre))
        {
            clear_all(&data);
            continue;
        }
        lstclear(&data.head);
		parser(&data.cmd, &data.pre, data.paths, data.envs);
//		traverse_parse_list(data.cmd);
        lstclear(&data.pre);
		add_history(data.str);
		//traverse_parse_list(data.cmd);
        excution(&data.envs, data.cmd, &pid, envp);
        free_cmd_list(&data.cmd);
		free(data.str);
		//system("leaks -q ms");
       // atexit(leak);
	}
}
