/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/24 19:25:44 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static int	up_date(t_env *env, char **old, char **curr, char *old_path)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
			curr = &env->value;
		else if (!ft_strcmp(env->key, "OLDPWD"))
			old = &env->value;
		if (old && curr)
			break ;
		env = env->next;
	}
	if (curr)
	{
		free(*curr);
		*curr = getcwd(NULL, 0);
		if (*curr == NULL)
			return (perror("msh-0.1$ "), 1);
	}
	if (old)
	{
		free(*old);
		*old = old_path;
	}
	return (0);
}

void	search_path(t_env *env, char **home)
{
	*home = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			*home = ft_strtrim(env->value, "\x03");
			break ;
		}
		env = env->next;
	}
}

int	ft_cd(char *path, t_env *env)
{
	char	**old;
	char	**curr;
	char	*old_path;
	char	*home_path;

	old = NULL;
	curr = NULL;
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (perror("msh-0.1$ "), 1);
	if (!path)
	{
		search_path(env, &home_path);
		if (home_path == NULL || chdir(home_path))
		{
			free(home_path);
			free(old_path);
			return (printf("msh-0.1$: HOME not set\n"), 1);
		}
		free(home_path);
	}
	else if (chdir(path))
		return (perror("cd"), free(old_path), 1);
	return (up_date(env, old, curr, old_path));
}
