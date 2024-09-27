/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/27 20:40:47 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	excute(t_cmd *cmd, t_red_info *red_info, t_env **env, char **envp)
{
	int	state;

	if (cmd->is_herdc && red_info->nmbr_cmd_herdc == 1)
	{
		close(red_info->fd[1]);
		dup2(red_info->fd[0], STDIN_FILENO);
		close(red_info->fd[0]);
	}
	if (red_info->fd_out != -5)
		dup2(red_info->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(red_info->pfds[1], STDOUT_FILENO);
	if (red_info->red_input)
		dup2(red_info->fd_inp, STDIN_FILENO);
	else if (cmd->is_herdc == false && red_info->prev > 0)
		dup2(red_info->prev, STDIN_FILENO);
	close(red_info->pfds[0]);
	close(red_info->pfds[1]);
	state = is_bultin(env, cmd, red_info->is_one_cmd);
	if (state == 1)
		exit(1);
	else if (!state)
		exit(0);
	if (execve(cmd->path, cmd->args, envp) == -1)
		error(errno, cmd->cmd);
}

void	child(t_cmd *cmd, t_red_info *red_info, t_env **env, char **envp)
{
	int	out[2];

	red_info->herdc_content = NULL;
	red_info->red_input = NULL;
	red_info->red_out = NULL;
	red_info->fd_out = -5;
	signal(SIGINT, SIG_DFL);
	if (cmd->redirections && (!cmd->is_herdc || red_info->nmbr_cmd_herdc == 1)
		&& !implement_redirections(cmd->redirections, red_info, *env, false))
	{
		free(red_info->herdc_content);
		exit(1);
	}
	if (!cmd->cmd)
		exit(0);
	if (cmd->is_herdc && red_info->nmbr_cmd_herdc != 1)
	{
		if (pipe(red_info->pfds) == -1)
			return (perror("msh-0.1$ "), exit(errno));
		write(out[1], "", 1);
		close(out[1]);
		dup2(out[0], STDIN_FILENO);
		close(out[0]);
	}
	excute(cmd, red_info, env, envp);
}

void	exit_state(t_env **env, int state, int smpl_state, char **envp)
{
	char		*tmp;
	static int	prev_sate;

	if (state == -1 && smpl_state == -1 && prev_sate == -32)
	{
		free_envp(envp);
		return ;
	}
	prev_sate = smpl_state;
	tmp = (*env)->value;
	if (WIFSIGNALED(state))
		state = WTERMSIG(state) + 128;
	else if (g_pid == -42)
		state = 1;
	else if (smpl_state != -1 && smpl_state != -33 && smpl_state != -32)
		state = smpl_state;
	else
		state = WEXITSTATUS(state);
	(*env)->value = ft_itoa(state);
	free(tmp);
	if (smpl_state != -33 && smpl_state != -32)
	{
		free_envp(envp);
		envp = NULL;
	}
}

int	logic(t_cmd *cmd, t_red_info *red_info, t_env **env, char **envp)
{
	int	sampel_state;

	sampel_state = -1;
	if (pipe(red_info->pfds) == -1)
		return (perror("msh-0.1$ "), exit_state(env, errno, -1, envp), -33);
	g_pid = fork();
	if (g_pid == -1)
		return (close(red_info->pfds[0]), close(red_info->pfds[1]),
			perror("msh-0.1$ "), exit_state(env, errno, -1, envp), -33);
	if (g_pid == 0)
		child(cmd, red_info, env, envp);
	if (cmd->is_herdc == true && red_info->nmbr_cmd_herdc == 1
		&& red_info->nmbr_cmd_herdc--)
		close(red_info->fd[0]);
	if (g_pid != -42 && red_info->is_one_cmd && cmd && cmd->cmd)
		sampel_state = sample_bultin(env, cmd, red_info);
	if (red_info->prev > -1)
		close(red_info->prev);
	if (g_pid != -42 && cmd->next)
		red_info->prev = dup(red_info->pfds[0]);
	close(red_info->pfds[0]);
	close(red_info->pfds[1]);
	return (sampel_state);
}

void	excution(t_env **env, t_cmd *cmd, int *pid)
{
	int			state;
	int			sampel_state;
	t_red_info	red_info;
	char		**new_envp;

	state = -1;
	new_envp = NULL;
	if (!cmd)
		return ;
	new_envp = pre_excution(env, cmd, &red_info, new_envp);
	while (*pid != -42 && cmd)
	{
		sampel_state = logic(cmd, &red_info, env, new_envp);
		if (cmd && cmd->is_herdc == true)
		{
			red_info.nmbr_cmd_herdc--;
		}
		cmd = cmd->next;
	}
	while (wait(&state) >= 0)
	{
	}
	exit_state(env, state, sampel_state, new_envp);
}
