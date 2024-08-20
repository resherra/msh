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
		perror ("msh-0.1$ ");
	}
		exit(0) ;
}

void excution(t_env **env, t_cmd *cmd, char **envp)
{
    int prev;
    int pfds[2];
    int id;
	int i;
	
	i = 0;
	prev = -1;
	if (cmd && cmd ->cmd && !cmd->next)
	{
		if (is_bultin(env, cmd))
			cmd = cmd->next;
	}
    while (cmd)
    {
		if (!cmd->path)
			printf("msh-0.1$: %s: command not found\n", cmd->cmd);
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
	{
	}	
}
