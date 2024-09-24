/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_of_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/24 04:11:20 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	handle_herdc_inp(int *fd, int *out, t_red_info *red_info)
{
	if (pipe(fd) < 0)
		return (perror("msh-01$: "), free(red_info->herdc_content),
			exit(errno));
	if (red_info->nmbr_cmd_herdc == 1)
		return (write(red_info->fd[1], red_info->herdc_content,
				ft_strlen(red_info->herdc_content)), exit(0));
	else if (red_info->fd_out != -5)
		write(fd[1], red_info->herdc_content,
			ft_strlen(red_info->herdc_content));
	else
	{
		write(fd[1], "", 1);
		if (pipe(out) < 0)
			return (perror("msh-01$: "), exit(errno));
		dup2(out[1], STDOUT_FILENO);
		close(out[0]);
		close(out[1]);
	}
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
	int	out[2];
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
	if (!red_info->herdc_content)
			exit(0);
	handle_herdc_inp(fd, out, red_info);
	if (red_info->fd_out != -5)
	{
		state = is_bultin(&env, cmd, red_info->is_one_cmd);
		if (state == 1 || !state)
			exit(state);
	}
	if (execve(cmd->path, cmd->args, envp) == -1)
		error(errno, cmd->path);
}

// void	exit_state(t_env **env, int state, int smpl_state, char **envp)
// {
// 	char	*tmp;

// 	tmp = (*env)->value;
// 	if (smpl_state != -1 && smpl_state != 2)
// 		state = smpl_state;
// 	else
// 		state = WEXITSTATUS(state);
// 	(*env)->value = ft_itoa(state);
// 	free(tmp);
// 	free_envp(envp);
// }

void	excute_heredocs(t_env **env, t_cmd *cmd, t_red_info *red_info,
		char **envp)
{

	if (pipe(red_info->fd) < 0)
		return (exit_state(env, 1, -1, envp));
	red_info->nmbr_cmd_herdc = cmd->nmbr_of_herdc;
	while (cmd)
	{
		if (cmd->is_herdc == true)
		{
			g_pid = fork();
			if (g_pid == -1)
				return (perror("msh-0.1$ "), exit_state(env, 1, -1, envp));
			if (g_pid == 0)
				herdc_child(cmd, red_info, *env, envp);
			red_info->nmbr_cmd_herdc--;
			waitpid(g_pid, NULL, 0);
		}
		if (g_pid == -42)
		{
			//exit_state(env, 1, -1, envp);
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