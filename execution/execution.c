/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/22 21:52:49 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

// #define sa_handler __sigaction_u.__sa_handler
// #define sa_sigaction __sigaction_u.__sa_sigaction
		
void	error(int err, char *path)
{
	int	prev_errno;

	prev_errno = err;
	 if (!path)
	 	exit(0);
	if (opendir(path) != NULL)
		return (printf("msh-0.1$: %s: is a directory\n", path), exit(126));
	else if (!ft_strchr(path,'/') && prev_errno == ENOENT)
	{
		write(2, "msh-0.1$: ", 10);
		write(2, path, ft_strlen(path));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else if (prev_errno == ENOENT)
		return (perror("msh-0.1$ "), exit(127));
	if (EACCES == prev_errno)
	{
		printf("msh-0.1$: %s\n", strerror(prev_errno));
		exit(126);
	}
	perror ("msh-0.1$ ");
	exit(err);
}

void excute(t_cmd *cmd, int *pfds, t_red_info *red_info, t_env **env, char **envp)
{
	int state;

	if (cmd->is_herdc && red_info->nmbr_cmd_herdc == 1)
	{
		close(red_info->fd[1]);
		dup2(red_info->fd[0], STDIN_FILENO);
		close(red_info->fd[0]);
	}
	if (red_info->fd_out != -5)
	 	dup2(red_info->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(pfds[1],STDOUT_FILENO);
	if (red_info->red_input)
		dup2(red_info->fd_inp, STDIN_FILENO);
     else if (cmd->is_herdc == false && red_info->prev > 0 )
		dup2(red_info->prev,STDIN_FILENO);
	close(pfds[0]);
	close(pfds[1]);
	state = is_bultin(env, cmd, red_info->is_one_cmd);
	if (state == 1)
		exit(1) ;
	else if (!state )
		exit(0);
	if (execve(cmd->path, cmd->args, envp) == -1)
		error(errno, cmd->path);
}

void child(t_cmd *cmd, int *pfds, t_red_info *red_info, t_env **env, char **envp)
{
	red_info->herdc_content = NULL;
	red_info->red_input = NULL;
	red_info->red_out = NULL;
	red_info->fd_out = -5;

	signal(SIGINT, SIG_DFL);
	if (cmd->redirections && !implement_redirections(cmd->redirections , red_info, *env, false))
	{
		free(red_info->herdc_content);
		exit(1);
	}
	if (!cmd->cmd)
		exit(0);
	excute(cmd, pfds, red_info, env, envp);
}

static void free_envp(char **envp)
{
    int i = 0;

	if (!envp)
		return ;
    while (envp[i])
	{
        free(envp[i]);
		i++;
	}
    free(envp);
}

void handle_herdc_inp(int *fd, int *out,t_red_info *red_info)
{
	int counter;

	counter = red_info->nmbr_cmd_herdc;
	if (pipe(fd) < 0)
		return (perror("msh-01$: "), free(red_info->herdc_content), exit(errno));
	if (counter == 1)
		return (write(red_info->fd[1], red_info->herdc_content, ft_strlen(red_info->herdc_content)), exit(0));
	else if (red_info->fd_out != -5)
		write(fd[1], red_info->herdc_content, ft_strlen(red_info->herdc_content));
	else
	{
		write(fd[1], "", 1);
		if (pipe(fd) < 0)
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

void herdc_child(t_cmd *cmd, t_red_info *red_info, t_env *env, char **envp)
{
	red_info->herdc_content = NULL;
	red_info->red_input = NULL;
	red_info->red_out = NULL;
	red_info->fd_out = -5;
	int fd[2];
	int out[2];
	int state;

	signal(SIGINT, SIG_DFL);
	if (cmd->redirections && !implement_redirections(cmd->redirections , red_info, env, true))
		return(free(red_info->herdc_content), exit(1));
	if (!cmd->cmd)
		exit(0);
	if (red_info->herdc_content)
		handle_herdc_inp(fd, out, red_info);
	if (red_info->fd_out != -5)
	{
		state = is_bultin(&env, cmd, red_info->is_one_cmd);
		if (state == 1 || !state)
			exit(state) ;
	}
	if (execve(cmd->path, cmd->args, envp) == -1)
		error(errno, cmd->path);
}

void exit_state(t_env **env, int state, int smpl_state, char **envp)
{
	char	*tmp;

	tmp = (*env)->value;
	if (smpl_state != -1 && smpl_state != 2)
		state = smpl_state;
	else
		state = WEXITSTATUS(state);
	(*env)->value = ft_itoa(state);
	free(tmp);
	free_envp(envp);
}

void excute_heredocs(t_env **env, t_cmd *cmd, int *pid, t_red_info *red_info, char **envp)
{
	pipe(red_info->fd);
	red_info->nmbr_cmd_herdc = cmd->nmbr_of_herdc;
	if (cmd && !cmd->next)
		red_info->is_one_cmd = true;
	while (cmd)
	{
		if (cmd->is_herdc == true)
		{
			*pid = fork();
			if (*pid == -1)
				return (perror("msh-0.1$ "), exit_state(env, 1, -1, envp));
			if (*pid == 0)
				herdc_child(cmd, red_info, *env, envp);
			red_info->nmbr_cmd_herdc--;
			waitpid(*pid, NULL, 0); 
		}
		if (*pid == -42)
		{
			exit_state(env, 1, -1, envp);
			close(red_info->fd[0]);
			break;
		}
		cmd = cmd->next;
	}
}


void excution(t_env **env, t_cmd *cmd, int *pid, char**envp)
{
    int pfds[2];
	int i;
	int state;
	int sampel_state;
	t_red_info red_info;
    char **new_envp = NULL;

    i = 0;
	sampel_state = -1;
	red_info.prev = -1;
	state = 0;
	red_info.is_one_cmd = false;
	if (!cmd)
		return ;
	new_envp = lst_to_envp(*env);
	if (cmd && cmd->nmbr_of_herdc)
	{
		excute_heredocs(env, cmd, pid, &red_info, envp);
		close(red_info.fd[1]);
	}
	red_info.nmbr_cmd_herdc = cmd->nmbr_of_herdc;
	while (*pid != -42 && cmd)
	{
		if (cmd && cmd->is_herdc == true && red_info.nmbr_cmd_herdc != 1)
		{
			red_info.nmbr_cmd_herdc--;
			cmd = cmd->next;
			continue;
		}
		if (pipe(pfds) == -1)
			return (perror("msh-0.1$ "), exit_state(env, errno, -1, envp));
		*pid = fork();
		if (*pid == -1)
			return (close(pfds[0]),close(pfds[1]),perror("msh-0.1$ "), exit_state(env, errno, -1, envp));
        if (*pid == 0)
			child(cmd, pfds, &red_info, env, new_envp);
		if (cmd->is_herdc == true && red_info.nmbr_cmd_herdc == 1 && red_info.nmbr_cmd_herdc--)
			close(red_info.fd[0]);
		if (*pid != -42 && red_info.is_one_cmd && cmd && cmd->cmd)
			sampel_state = sample_bultin(env, cmd, &red_info);
		if (i++ > 0)
			close(red_info.prev);
		if (*pid != -42 && cmd->next)
			red_info.prev = dup(pfds[0]);
		close(pfds[0]);
		close(pfds[1]);
		cmd = cmd->next;
    }
	while (wait(&state) >= 0)
	{}
	exit_state(env, state, sampel_state, new_envp);
}
