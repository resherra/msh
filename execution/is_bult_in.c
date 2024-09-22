#include "../init.h"

int is_bultin(t_env **envs, t_cmd *cmd, int is_one)
{
	if (!ft_strcmp("exit", cmd->cmd))
		return (0);
    if (!ft_strcmp("env", cmd->cmd))
        return (env(*envs, cmd)); 
	else if (!ft_strcmp("echo", cmd->cmd))
		return (ft_echo(cmd->args));
    else if (!ft_strcmp("export", cmd->cmd))
	{
		if (!is_one)
        	return (ft_export(*envs, cmd->args)); 
		return (0);
	}
    else if (!ft_strcmp("unset", cmd->cmd))
	{
		if (!is_one)
        	return (unset(envs, cmd->args)); 
		return (0);
	}
	else if (!ft_strcmp("cd", cmd->cmd))
	{
		if (!is_one)
			return (ft_cd(cmd->args[1], *envs));
		return (0);
	}
	else if (!ft_strcmp("pwd", cmd->cmd))
		return (pwd());
	
	return(2);
}

int sample_bultin(t_env **envs, t_cmd *cmd, t_red_info *redir_info)
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
	return(2);
}
