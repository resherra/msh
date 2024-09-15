#include "../init.h"

int is_bultin(t_env **envs, t_cmd *cmd, int is_one)
{
	if (!ft_strcmp("exit", cmd->cmd))
		return (0);
    if (!ft_strcmp("env", cmd->cmd))
        return (env(*envs)); 
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
	char	state[2];

    (void)redir_info;
	state[1] = 0;
	if (!ft_strcmp("exit", cmd->cmd))
		ft_exit(&cmd);
    else if (!strcmp("export", cmd->cmd))
    {
		state[0] = ft_export(*envs, cmd->args) + 48 ;
		(*envs)->value = ft_strdup(state);
        return (1);
    }
    else if (!ft_strcmp("unset", cmd->cmd))
    {
		state[0] = unset(envs, cmd->args) + 48;
        (*envs)->value = ft_strdup(state);
		return (1);
    } 
	else if (!ft_strcmp("cd", cmd->cmd))
	{
		state[0] = ft_cd(cmd->args[1], *envs) + 48;
		(*envs)->value = ft_strdup(state);
		return (1);
	}
	return(0);
}
