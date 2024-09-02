/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:28:46 by recherra          #+#    #+#             */
/*   Updated: 2024/09/02 17:28:47 by recherra         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	pre_path = ft_strjoin("/", cmd);
	if (!paths)
	{
		return (NULL);
	}
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
	if (!access(cmd, F_OK))
		return (cmd);
	//perror("msh-0.1$: ");
	return (NULL);
}
