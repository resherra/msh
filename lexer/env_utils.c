/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:31:56 by recherra          #+#    #+#             */
/*   Updated: 2024/08/17 01:47:47 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_env	*new_env(char *key, char *value)
{
    t_env	*new;

    new = malloc(sizeof(t_env));
    new->key = key;
    new->value = value;
    if (!value || !ft_strlen(value))
        new->in_export = true;
    else
        new->in_export = false;
    new->next = NULL;
    return (new);
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
		curr = curr->next;
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
