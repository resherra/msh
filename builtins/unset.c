/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:35:22 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 21:45:56 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	func(void *content)
{
	free(content);
}

int	check_identifier(char *str)
{
	int	var_len;

	var_len = 0;
	if (str[var_len] != '_' && !ft_isalpha(str[var_len++]))
	{
		printf("unset: `%s' : not a valid identifier\n", str);
		return (1);
	}
	while (str[var_len] != 0 && (ft_isalnum(str[var_len])
			|| str[var_len] == '_'))
	{
		var_len++;
	}
	if (str[var_len] == 0)
		return (0);
	printf("unset: `%s' : not a valid identifier\n", str);
	return (1);
}

int	unset(t_env **envs, char **vars)
{
	int		i;
	int		state;
	t_env	*curr;
	t_env	*prev;

	i = 1;
	state = 0;
	while (vars[i])
	{
		curr = *envs;
		prev = curr;
		state += check_identifier(vars[i++]);
		while (curr)
		{
			if (!ft_strcmp(vars[i - 1], curr->key))
			{
				prev->next = curr->next;
				env_delone(curr, func);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (state > 0);
}
