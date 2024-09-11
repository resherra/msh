#include "../init.h"

int is_bultin(t_env **envs, t_cmd *cmd)
{
	if (!ft_strcmp("exit", cmd->cmd))
		ft_exit(&cmd);
    else if (!ft_strcmp("env", cmd->cmd))
        return (env(*envs)); 
	else if (!ft_strcmp("echo", cmd->cmd))
		return (ft_echo(cmd->args));
    else if (!ft_strcmp("export", cmd->cmd))
        return (ft_export(*envs, cmd->args));
    else if (!ft_strcmp("unset", cmd->cmd))
        return (unset(envs, cmd->args)); 
	else if (!ft_strcmp("cd", cmd->cmd))
		return (ft_cd(cmd->args[1], *envs));
	else if (!ft_strcmp("pwd", cmd->cmd))
		return (pwd());
	
	return(2);
}

int sample_bultin(t_env **envs, t_cmd *cmd, t_red_info *redir_info)
{
	char	state[2];

	state[1] = 0;
	//implement_redirections(cmd->redirections, redir_info, *envs);
	if (!ft_strcmp("exit", cmd->cmd))
		ft_exit(&cmd);
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
		state[0] = ft_cd(cmd->args[1], *envs) + 48;
		(*envs)->value = ft_strdup(state);
		return (1);
	}
	return(0);
}
// int red_out(t_red *redir, t_red_info *redir_info)
// {
// 	int fd;

// 	fd = -1;
// 	if (redir->red_type == RED_OUT)
// 	{
// 		redir_info->red_out = redir->red_file;
// 		fd = open(redir_info->red_out, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
// 		if (fd < 0)
//         	return (perror("msh-0.1$ "), 0);
// 		redir_info->fd_out = -3;
// 	}
// 	else if (redir->red_type == RED_APP)
// 	{
// 		redir_info->red_out = redir->red_file;
// 		 fd = open(redir->red_file, O_CREAT | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
// 		if (fd < 0)
//        		return (perror("msh-0.1$ "), 0);
// 		redir_info->fd_out = -2;
// 	}
// 	close(fd);
// 	return(1);
// }
// int	open_files(t_red *redir, t_red_info *redir_info)
// {
// 	int fd;

// 	while (redir)
// 	{
// 		if (redir->is_ambegious)
// 		{
// 			write(2, "msh-0.1$ : ambiguous redirect\n", 31);
// 			return(0);
// 		}
// 		else if (redir->red_type == RED_IN)
// 		{
// 			fd = open(redir->red_file, O_RDWR);
// 			if (fd < 0)
// 				return(perror("msh-0.1$ "),free(redir_info->herdc_content), exit(1) ,0);
// 			redir_info->red_input = redir->red_file;
// 		}
// 		else if (!red_out(redir, redir_info))
// 			return (free(redir_info->herdc_content), exit(1), 0);
// 		redir = redir->next;
// 	}
// 	return (1);
// }