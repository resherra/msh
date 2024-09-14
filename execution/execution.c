#include "../init.h"

#define sa_handler __sigaction_u.__sa_handler
#define sa_sigaction __sigaction_u.__sa_sigaction
		
void	error(int err, char *path)
{
	int prev_errno = err;
	if (opendir(path))
	{
		printf("msh-0.1$: %s: is a directory\n", path);
		exit(126);
	}
	else if (!ft_strchr(path,'/') && prev_errno == ENOENT)
	{
		write(2, "msh-0.1$: ", 10);
		write(2, path, ft_strlen(path));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else if (prev_errno == ENOENT)
	{
		perror ("msh-0.1$ ");
		exit(127);
	}
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

	if (red_info->herdc_content)
	{
		close(red_info->fd[1]);
		dup2(red_info->fd[0], STDIN_FILENO);
		close(red_info->fd[0]);
	}
	if (red_info->fd_out != -1)
	 	dup2(red_info->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(pfds[1],STDOUT_FILENO);
	if (red_info->red_input)
		dup2(red_info->fd_inp, STDIN_FILENO);
     else if (red_info->prev > 0 )
		dup2(red_info->prev,STDIN_FILENO);
	close(pfds[0]);
	close(pfds[1]);
	state = is_bultin(env, cmd);
	if (state == 1)
		exit(1) ;
	else if (!state)
		exit(0);
	if (execve(cmd->path, cmd->args,envp) == -1)
		error(errno, cmd->path);
}

void child(t_cmd *cmd, int *pfds, t_red_info *red_info, t_env **env, char **envp)
{
	red_info->herdc_content = NULL;
	red_info->red_input = NULL;
	red_info->red_out = NULL;
	red_info->fd_out = -1;
	if (cmd->redirections && !implement_redirections(cmd->redirections , red_info, *env))
	{
		free(red_info->herdc_content);
		exit(1);
	}
	if (!cmd->cmd)
		exit(0);
	if (red_info->herdc_content)
	{
		if (pipe(red_info->fd) < 0)
			return (perror("msh-01$: "), free(red_info->herdc_content), exit(errno));
		write(red_info->fd[1], red_info->herdc_content, ft_strlen(red_info->herdc_content));
	}
	excute(cmd, pfds, red_info, env, envp);
}

void excution(t_env **env, t_cmd *cmd, char **envp, int *pid)
{
    int pfds[2];
	int i;
	int sta;
	t_red_info red_info;
    char *tmp = NULL;

    i = 0;
	red_info.prev = -1;
	sta = 0;
	if (cmd && cmd->cmd && !cmd->next)
		if (sample_bultin(env, cmd, &red_info))
			cmd = cmd->next;
    while (cmd)
    {
		pipe(pfds);
		*pid = fork();
        if (*pid == 0)
			child(cmd, pfds, &red_info, env, envp);
		if (i++ > 0 )
			close(red_info.prev);
		if (cmd->next)
			red_info.prev = dup(pfds[0]);
		close(pfds[0]);
		close(pfds[1]);
		cmd = cmd->next;
    }
	while (wait(&sta) >= 0)
	{}
	tmp = (*env)->value;
	(*env)->value = ft_itoa(WEXITSTATUS(sta));
	free(tmp);
}
