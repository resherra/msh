/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/24 19:26:21 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_env	*new_env_export(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->key = key;
	new->value = value;
	if (!value)
		new->in_export = true;
	else
		new->in_export = false;
	new->next = NULL;
	return (new);
}

static int	var_replace(t_env *curr, t_env *new)
{
	if (ft_strcmp(curr->key, new->key) == 0)
	{
		if (new->value != 0)
		{
			free(curr->value);
			curr->value = new->value;
			curr->in_export = false;
		}
		free(new->key);
		free(new);
		return (1);
	}
	return (0);
}

void	ft_env_addback(t_env **env, t_env *new)
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
			return ;
		curr = curr->next;
	}
	if (var_replace(curr, new))
		return ;
	curr->next = new;
}
