#include "../init.h"

int is_bultin(t_env **envs, t_cmd *cmd)
{
	if (!strcmp("exit", cmd->cmd))
			exit(0);
    else if (!strcmp("env", cmd->cmd))
    {
        return (env(*envs), 1);
    } 
	else if (!strcmp("echo", cmd->cmd))
	{
		return (ft_echo(cmd->args), 1);
	}
    else if (!strcmp("export", cmd->cmd))
    {
        return (ft_export(*envs, cmd->args), 1);
    }
    else if (!strcmp("unset", cmd->cmd))
    {
        return (unset(envs, cmd->args), 1);
    } 
	else if (!strcmp("cd", cmd->cmd))
	{
		return (ft_cd(cmd->args[1]), 1);
	}
	else if (!strcmp("pwd", cmd->cmd))
	{
		return (pwd(), 1);
	}
	
	return(0);
}
