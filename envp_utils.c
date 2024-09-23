/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:42:07 by recherra          #+#    #+#             */
/*   Updated: 2024/09/23 18:59:19 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	free_vars(char *trimmed_value, char *full_key)
{
	free(trimmed_value);
	free(full_key);
}

static int	get_the_size(t_env *envs)
{
	t_env	*curr;
	int		i;

	curr = envs;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

char	**lst_to_envp(t_env *envs)
{
	t_env		*new;
	t_util_vars	vars;
	char		**res;
	int			size;

	size = get_the_size(envs);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		exit(1);
	size = 0;
	new = envs->next;
	while (new)
	{
		if (new->in_export == FALSE)
		{
			vars.trimmed_value = ft_strtrim(new->value, "\x03");
			vars.full_key = ft_strjoin(new->key, "=");
			res[size++] = ft_strjoin(vars.full_key, vars.trimmed_value);
			free_vars(vars.trimmed_value, vars.full_key);
		}
		new = new->next;
	}
	res[size] = 0;
	return (res);
}
