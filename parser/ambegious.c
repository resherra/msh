/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambegious.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:27:26 by recherra          #+#    #+#             */
/*   Updated: 2024/09/02 17:27:29 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static int	check_n_files(char *str)
{
	char	*new;
	char	**res;
	int		i;

	new = ft_strtrim(str, "\x03");
	res = ft_split(new, ' ');
	free(new);
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (i);
}

int	check_ambg(char *str, t_env *envs)
{
	if (check_in_env(str, envs))
	{
		if (!ft_strcmp(str, "\x03") || check_n_files(str) != 1)
			return (1);
	}
	return (0);
}
