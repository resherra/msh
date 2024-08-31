/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:31:56 by recherra          #+#    #+#             */
/*   Updated: 2024/08/30 15:17:21 by apple            ###   ########.fr       */
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
	env = NULL;
}
