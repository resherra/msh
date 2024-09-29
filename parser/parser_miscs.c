/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:35:22 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 21:49:36 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	check_in_env(char *str, t_env *envs)
{
	t_env	*curr;

	curr = envs;
	while (curr)
	{
		if (!ft_strcmp(str, curr->value))
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	**lst_to_arr(int size, t_args *args_list)
{
	char	**args;
	t_args	*curr;
	int		i;

	args = malloc((sizeof(char *) * (size + 1)));
	if (!args)
		exit(1);
	curr = args_list;
	i = 0;
	while (curr)
	{
		if (i == 0)
			args[i] = ft_strdup(curr->str);
		else
			args[i] = ultimate_trim(curr->str);
		i++;
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

char	*abslt_rltv(char *pre_path)
{
	char	*path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(cwd, pre_path);
	if (!access(path, F_OK))
	{
		free(cwd);
		return (path);
	}
	free(cwd);
	free(path);
	path = NULL;
	return (path);
}

int	pth(char *paths, char **path, char **pre_path)
{
	*path = ft_strjoin(paths, *pre_path);
	if (!access(*path, F_OK))
	{
		free(*pre_path);
		return (1);
	}
	free(*path);
	return (0);
}

char	*extract_path(char *cmd, t_env *envs)
{
	char	*pre_path;
	char	*path;
	char	*curr_pth;
	char	**paths;

	if (!cmd || !(*cmd))
		return (NULL);
	paths = get_new_paths(envs);
	pre_path = ft_strjoin("/", cmd);
	if (*cmd == '/')
		return (free_and_return(pre_path, cmd, paths));
	if (*cmd == '.')
	{
		curr_pth = abslt_rltv(pre_path);
		if (curr_pth)
			return (free_and_return(pre_path, curr_pth, paths));
	}
	if (get_act_paths(paths, &path, &pre_path))
		return (path);
	if (!access(cmd, F_OK))
	{
		free(pre_path);
		return (cmd);
	}
	return (free_and_return(pre_path, cmd, paths));
}
