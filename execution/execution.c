#include "../init.h"

void excution(t_env **env, t_cmd *cmd)
{
    int prev;
    int pfds[2];
    int id, i = 0;
	char *envp[2];

	envp[0] = "TERM=xterm-256color";
	envp[1] = NULL ;
	
	if (cmd && cmd ->cmd && !cmd->next)
	{
		if (is_bultin(env, cmd))
			cmd = cmd->next;
	}
    while (cmd)
    {
		pipe(pfds);
        id = fork();
        if (id == 0)
        {
			if (cmd->redirections && !implement_redirections(cmd->redirections))
			{
				return ;
			}
			if (cmd->next)
				dup2(pfds[1],STDOUT_FILENO);
            if (i > 0)
				dup2(prev,STDIN_FILENO);
			close(pfds[0]);
			close(pfds[1]);
			if (cmd->cmd && is_bultin(env, cmd))
			{
				exit(0);
			}
			else if (cmd->cmd && execve(cmd->path, cmd->args, envp) == -1)
			 {
				perror ("msh-0.1$ ");
			 }
				exit(1) ;
		}
		if (i > 0 )
			close(prev);
		if (cmd->next)
			prev = dup(pfds[0]);
		close(pfds[0]);
		close(pfds[1]);
        i++;
		cmd =cmd->next;
    }
	while (wait(NULL) >= 0)
	{
	}	
}
