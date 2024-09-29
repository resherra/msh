/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/26 18:28:25 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	error(int err, char *path)
{
	int	prev_errno;

	prev_errno = err;
	if (!path)
		exit(0);
	if (opendir(path) != NULL)
		return (printf("msh-0.1$: %s: is a directory\n", path), exit(126));
	else if (!*path || (!ft_strchr(path, '/') && prev_errno == ENOENT))
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
	perror("msh-0.1$ ");
	exit(err);
}

int	is_bultin(t_env **envs, t_cmd *cmd, int is_one)
{
	int	sampel;

	sampel = 1;
	if (!ft_strcmp("exit", cmd->cmd))
		return (0);
	if (!ft_strcmp("env", cmd->cmd))
		return (env(*envs, cmd));
	else if (!ft_strcmp("echo", cmd->cmd))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp("export", cmd->cmd) && sampel-- && !is_one)
		return (ft_export(*envs, cmd->args));
	else if (!ft_strcmp("unset", cmd->cmd) && sampel-- && !is_one)
		return (unset(envs, cmd->args));
	else if (!ft_strcmp("cd", cmd->cmd) && sampel-- && !is_one)
		return (ft_cd(cmd->args[1], *envs));
	else if (!ft_strcmp("pwd", cmd->cmd))
		return (pwd());
	if (sampel == 0)
		return (0);
	return (2);
}

int	sample_bultin(t_env **envs, t_cmd *cmd, t_red_info *redir_info)
{
	(void)redir_info;
	if (!ft_strcmp("exit", cmd->cmd))
		return (ft_exit(cmd));
	else if (!strcmp("export", cmd->cmd))
	{
		return (ft_export(*envs, cmd->args));
	}
	else if (!ft_strcmp("unset", cmd->cmd))
	{
		return (unset(envs, cmd->args));
	}
	else if (!ft_strcmp("cd", cmd->cmd))
	{
		return (ft_cd(cmd->args[1], *envs));
	}
	return (-1);
}
