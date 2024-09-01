#include "../init.h"

int is_bultin(t_env **envs, t_cmd *cmd)
{
	if (!ft_strcmp("exit", cmd->cmd))
	{
		ft_exit(&cmd);
	}
    else if (!ft_strcmp("env", cmd->cmd))
    {
        return (env(*envs), 1);
    } 
	else if (!ft_strcmp("echo", cmd->cmd))
	{
		return (ft_echo(cmd->args), 1);
	}
    else if (!ft_strcmp("export", cmd->cmd))
    {
        return (ft_export(*envs, cmd->args), 1);
    }
    else if (!ft_strcmp("unset", cmd->cmd))
    {
        return (unset(envs, cmd->args), 1);
    } 
	else if (!ft_strcmp("cd", cmd->cmd))
	{
		return (ft_cd(cmd->args[1]), 1);
	}
	else if (!ft_strcmp("pwd", cmd->cmd))
	{
		return (pwd(), 1);
	}
	
	return(0);
}

int sample_bultin(t_env **envs, t_cmd *cmd)
{
	char	state[2];


	if (!ft_strcmp("exit", cmd->cmd))
	{
		ft_exit(&cmd);
	}
    else if (cmd->args[1] && !strcmp("export", cmd->cmd))
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
		state[0] = ft_cd(cmd->args[1]) + 48;
		(*envs)->value = ft_strdup(state);
		return (1);
	}
	return(0);
}
