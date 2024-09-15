/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:28:46 by recherra          #+#    #+#             */
/*   Updated: 2024/09/15 02:20:48 by apple            ###   ########.fr       */
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
		args[i++] = ft_strdup(curr->str);
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

char	*extract_path(char *cmd, char **paths)
{
	char	*pre_path;
	char	*path;
	char	*cur;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);

	pre_path = ft_strjoin("/", cmd);
	if (cmd[0] &&  cmd[0] == '.' && cmd[1] == '/')
	{
		cur = getcwd(NULL, 0);
		path = ft_strjoin(cur, pre_path);
		free(cur);
		return (free(pre_path), path);
	}
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], pre_path);
		if (!access(path, F_OK))
		{
			free(pre_path);
			return (path);
		}
		free(path);
		i++;
	}
	free(pre_path);
	return (cmd);
}
