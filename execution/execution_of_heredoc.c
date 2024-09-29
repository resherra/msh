/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_of_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/26 18:28:28 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"      

void	handle_herdc_inp(int *fd, t_red_info *red_info)
{
	if (pipe(fd) < 0)
		return (perror("msh-01$: "), free(red_info->herdc_content),
			exit(errno));
	if (red_info->nmbr_cmd_herdc == 1 && red_info->herdc_content)
		return (write(red_info->fd[1], red_info->herdc_content,
				ft_strlen(red_info->herdc_content)), exit(0));
	else if (red_info->fd_out != -5 && red_info->herdc_content)
		write(fd[1], red_info->herdc_content,
			ft_strlen(red_info->herdc_content));
	else
		exit(0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (red_info->fd_out != -5)
		dup2(red_info->fd_out, STDOUT_FILENO);
	if (red_info->red_input)
		dup2(red_info->fd_inp, STDIN_FILENO);
}

void	herdc_child(t_cmd *cmd, t_red_info *red_info, t_env *env, char **envp)
{
	int	fd[2];
	int	state;

	red_info->herdc_content = NULL;
	red_info->red_input = NULL;
	red_info->red_out = NULL;
	red_info->fd_out = -5;
	signal(SIGINT, SIG_DFL);
	if (cmd->redirections && !implement_redirections(cmd->redirections,
			red_info, env, true))
		return (free(red_info->herdc_content), exit(1));
	if (!cmd->cmd)
		exit(0);
	handle_herdc_inp(fd, red_info);
	if (red_info->fd_out != -5)
	{
		state = is_bultin(&env, cmd, red_info->is_one_cmd);
		if (state == 1 || !state)
			exit(state);
	}
	if (execve(cmd->path, cmd->args, envp) == -1)
		exit(0);
}

void	excute_heredocs(t_env **env, t_cmd *cmd, t_red_info *red_info,
		char **envp)
{
	if (pipe(red_info->fd) < 0)
		return (exit_state(env, errno, -32, envp));
	red_info->nmbr_cmd_herdc = cmd->nmbr_of_herdc;
	while (cmd)
	{
		if (cmd->is_herdc == true)
		{
			g_pid = fork();
			if (g_pid == -1)
				return (perror("msh-0.1$ "), exit_state(env, errno, -32, envp));
			if (g_pid == 0)
				herdc_child(cmd, red_info, *env, envp);
			red_info->nmbr_cmd_herdc--;
			waitpid(g_pid, NULL, 0);
		}
		if (g_pid == -42)
		{
			close(red_info->fd[0]);
			close(red_info->fd[1]);
			break ;
		}
		cmd = cmd->next;
	}
}

char	**pre_excution(t_env **env, t_cmd *cmd, t_red_info *red_info,
		char **envp)
{
	red_info->prev = -1;
	red_info->is_one_cmd = false;
	envp = lst_to_envp(*env);
	if (cmd && !cmd->next)
		red_info->is_one_cmd = true;
	if (cmd && cmd->nmbr_of_herdc)
	{
		excute_heredocs(env, cmd, red_info, envp);
		close(red_info->fd[1]);
	}
	red_info->nmbr_cmd_herdc = cmd->nmbr_of_herdc;
	return (envp);
}
