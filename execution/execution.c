#include "../init.h"

#define sa_handler __sigaction_u.__sa_handler
#define sa_sigaction __sigaction_u.__sa_sigaction
		
void child(t_cmd *cmd, int *pfds, t_red_info *red_info, t_env **env, char **envp)
{
	// if (cmd->redirections && !implement_redirections(cmd->redirections))
	// {
	// 	return ;
	// }
	if (red_info->herdc_content /*&& !cmd->next*/)
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
	{
		dup2(red_info->fd_inp, STDIN_FILENO);
	}
     else if (red_info->prev > 0 )
		dup2(red_info->prev,STDIN_FILENO);
	close(pfds[0]);
	close(pfds[1]);
	if (cmd->cmd && is_bultin(env, cmd))
		exit(0);
	else if (/*cmd->path &&*/ cmd->cmd && execve(cmd->path, cmd->args,envp) == -1)
	{
		if (errno == ENOENT)
		{
				write(2, "msh-0.1$: ", 10);
			 	write(2, cmd->cmd, ft_strlen(cmd->cmd));
			 	write(2, ": command not found\n", 20);
			exit(127);
		}
		perror ("msh-0.1$ ");
		if (EACCES == errno)
		{
			exit(126);
		}
		exit(errno);
	}
	// else if (!cmd->path)
	// {
	// 	write(2, "msh-0.1$: ", 10);
	// 	write(2, cmd->cmd, ft_strlen(cmd->cmd));
	// 	write(2, ": command not found\n", 20);
	// 	exit(127);
	// }
	// 	exit(1) ;
}

void excution(t_env **env, t_cmd *cmd, char **envp, int *pid)
{
    int pfds[2];
    int id;
	int i;
	int sta;
	int *k = pid;
	t_red_info red_info;

	i = 0;
	red_info.prev = -1;
	sta = 0;
	if (cmd && cmd->cmd && !cmd->next)
		if (sample_bultin(env, cmd) && !cmd->redirections)
			cmd = cmd->next;
    while (cmd)
    {
		red_info.herdc_content = NULL;
		if (cmd->redirections && !implement_redirections(cmd->redirections , &red_info, k))
		{
			//write(2, "her\n", 4);
			return ;
		}
		if (red_info.herdc_content)
			pipe(red_info.fd);
		pipe(pfds);
        id = fork();
		*pid = id;
        if (id == 0)
		{
			child(cmd, pfds, &red_info, env, envp);
		}
		if (red_info.herdc_content)
		 {
		 	close(red_info.fd[0]); 
		 	write(red_info.fd[1], red_info.herdc_content, ft_strlen(red_info.herdc_content));
		 	close(red_info.fd[1]); 
		 }
		if (i++ > 0 )
			close(red_info.prev);
		if (cmd->next)
			red_info.prev = dup(pfds[0]);
		close(pfds[0]);
		close(pfds[1]);
		cmd =cmd->next;
    }
	while (wait(&sta) >= 0)
	{}
	//printf(">>%i\n", WEXITSTATUS(sta));
	(*env)->value = ft_itoa(WEXITSTATUS(sta));
}
