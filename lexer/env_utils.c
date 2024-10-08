/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:35:22 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 21:48:54 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->key = key;
	new->value = ft_strjoin(value, "\x03");
	if (!value || !ft_strlen(value) || !ft_strcmp(new->value, "\x03"))
		new->in_export = true;
	else
		new->in_export = false;
	new->next = NULL;
	free(value);
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
