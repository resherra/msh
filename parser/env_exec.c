/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:30:32 by recherra          #+#    #+#             */
/*   Updated: 2024/09/02 17:30:41 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static void	safe_move(t_args **args_list)
{
	t_args	*tmp;

	tmp = *args_list;
	*args_list = (*args_list)->next;
	free(tmp->str);
	free(tmp);
}

int	treat_env(t_args **args_list)
{
	char	*new;
	char	**res;
	int		i;
	int		tmp;

	new = ft_strtrim((*args_list)->str, "\x03");
	res = ft_split(new, ' ');
	free(new);
	i = 0;
	while (res[i])
		i++;
	if (i > 0)
		safe_move(args_list);
	tmp = i;
	tmp--;
	while (tmp >= 0)
	{
		arg_add_front(args_list, new_arg(res[tmp]));
		tmp--;
	}
	free(res);
	return (i);
}
