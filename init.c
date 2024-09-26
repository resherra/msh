/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/26 03:56:00 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	handler(int sign)
{
	(void)sign;
	printf("\n");
	if (g_pid != -2 && g_pid != -3)
		g_pid = -42;
	else
	{
		g_pid = -3;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void static	setup(char **str, t_env **envs)
{
	g_pid = -2;
	*str = readline("msh-0.1$ ");
	if (g_pid == -3)
		(*envs)->value = ft_strdup("1");
	if (!(*str))
	{
		printf("exit\n");
		exit(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (1);
	init_all(&data);
	init_env(&data.envs, envp, &data.paths);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	while (1)
	{
		setup(&data.str, &data.envs);
		if (lexer(data.str, &data.head, data.envs, &data.pre))
		{
			clear_all(&data);
			continue ;
		}
        printf("\n\n");
        traverse_primary_tokens_list(data.head);
        printf("\n\n");
        lstclear(&data.head);
		parser(&data.cmd, &data.pre, data.paths, data.envs);
        printf("\n\n");
         traverse_primary_tokens_list(data.pre);
        printf("\n\n");
        lstclear(&data.pre);
		add_history(data.str);
         printf("\n\n\n");
         traverse_parse_list(data.cmd);
         printf("\n\n\n");
		excution(&data.envs, data.cmd, &g_pid);
		free_cmd_list(&data.cmd);
		free(data.str);
		//system("leaks -q ms");
	}
}
