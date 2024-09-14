/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:02:02 by recherra          #+#    #+#             */
/*   Updated: 2024/08/28 11:02:21 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static void	get_paths(char *value, char ***paths)
{
	*paths = ft_split(value, ':');
}

void	env_add_front(t_env **env, t_env *new)
{
	if (!env)
		return ;
	if (*env && new)
	{
		new->next = *env;
		*env = new;
	}
	else
		*env = new;
}

static void	extract_env(t_env **envs, char *str, char ***paths)
{
	int		i;
	t_env	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new = new_env(ft_substr(str, 0, i), ft_substr(str, i + 1, ft_strlen(str)));
	if (!ft_strcmp("PATH", new->key))
	{
		get_paths(new->value, paths);
	}
	env_addback(envs, new);
}

void	init_env(t_env **env, char **envp, char ***paths)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		extract_env(env, envp[i], paths);
		i++;
	}
	t_env *new = new_env(ft_strdup("?"), ft_strdup("0"));
	env_add_front(env, new);
}
