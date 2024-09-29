/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 20:00:08 by schakkou         ###   ########.fr       */
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

static void	setup(char **str, t_env **envs)
{
	char	*tmp;

	tmp = (*envs)->value;
	g_pid = -2;
	*str = readline("msh-0.1$ ");
	if (g_pid == -3)
	{
		(*envs)->value = ft_strdup("1");
		free(tmp);
	}
	if (!(*str))
	{
		ft_exit(NULL, (*envs)->value);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (1);
	init_all(&data);
	init_env(&data.envs, envp);
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
		lstclear(&data.head);
		parser(&data.cmd, &data.pre, data.envs);
		lstclear(&data.pre);
		add_history(data.str);
		excution(&data.envs, data.cmd, &g_pid);
		free_cmd_list(&data.cmd);
		free(data.str);
	//	system("leaks ms");
	}
}
