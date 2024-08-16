/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:31:56 by recherra          #+#    #+#             */
/*   Updated: 2024/07/22 04:33:34 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_env	*new_env(char *key, char *value)
{
    t_env	*new;

    new = malloc(sizeof(t_env));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

int	var_replace(t_env *curr, t_env *new)
{
	if (strcmp(curr->key, new->key) == 0)
	{
		if (ft_strlen(curr->value) != 0 &&  ft_strlen(new->value) == 0)
			return 1;
		curr->value = new->value;
		curr->in_export = false;
		return 1;
	}
	return 0;
}

void	env_addback(t_env **env, t_env *new)
{
	t_env	*curr;

	if (!env)
		return ;
	if (!(*env))
	{
		*env = new;
		return ;
	}
	curr = *env;
	while (curr->next)
	{
		if (var_replace(curr, new))
			return;
		curr = curr->next;
	}
	if (var_replace(curr, new))
		return;
	curr->next = new;
}

void	env_delone(t_env *env, void (*del)(void *))
{
    if (!env || !del)
        return ;
    del(env->key);
    del(env->value);
    free(env);
}

void	get_paths(char *value, char ***paths)
{
	*paths = ft_split(value, ':');
}


void	extract_env(t_env **envs, char *str, char ***paths)
{
	int		i;
	t_env	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new = new_env(ft_substr(str, 0, i), ft_substr(str, i + 1, ft_strlen(str)));
	if (!strcmp("PATH", new->key))
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
}
