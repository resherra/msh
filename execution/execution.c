#include "../init.h"

void child(t_cmd *cmd, int *pfds, int prev, t_env **env, char **envp)
{
	if (cmd->redirections && !implement_redirections(cmd->redirections))
	{
		return ;
	}
	if (cmd->next)
		dup2(pfds[1],STDOUT_FILENO);
	if (prev > -1)
		dup2(prev,STDIN_FILENO);
	close(pfds[0]);
	close(pfds[1]);
	if (cmd->cmd && is_bultin(env, cmd))
	{
		exit(0);
	}
	else if (cmd->path && cmd->cmd && execve(cmd->path, cmd->args,envp) == -1)
	{
		(*env)->value = 1;
		perror ("msh-0.1$ ");
	}
	else if (!cmd->path)
	{
		write(2, "msh-0.1$: ", 10);
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ": command not found\n", 20);
		(*env)->value = 127;
	}
		exit(1) ;
}

void excution(t_env **env, t_cmd *cmd, char **envp)
{
    int prev;
    int pfds[2];
    int id;
	int i;
	
	i = 0;
	prev = -1;
	if (cmd && cmd->cmd && !cmd->next)
		if (sample_bultin(env, cmd) && !cmd->redirections)
			cmd = cmd->next;
    while (cmd)
    {
		pipe(pfds);
        id = fork();
        if (id == 0)
			child(cmd, pfds, prev, env, envp);
		if (i++ > 0 )
			close(prev);
		if (cmd->next)
			prev = dup(pfds[0]);
		close(pfds[0]);
		close(pfds[1]);
		cmd =cmd->next;
    }
	while (wait(NULL) >= 0)
	{}
}
