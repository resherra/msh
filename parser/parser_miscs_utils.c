/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:12:58 by recherra          #+#    #+#             */
/*   Updated: 2024/09/28 20:13:07 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

char	**get_new_paths(t_env *envs)
{
	t_env	*curr;
	char	**paths;

	curr = envs;
	paths = NULL;
	while (curr)
	{
		if (!ft_strcmp("PATH", curr->key))
		{
			paths = get_paths(curr->value);
			return (paths);
		}
		curr = curr->next;
	}
	return (paths);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

int	get_act_paths(char **paths, char **path, char **pre_path)
{
	int i;

	i = 0;
	while (paths[i])
	{
		if (pth(paths[i++], path, pre_path))
		{
			free_paths(paths);
			return (1);
		}
	}
	return (0);
}