/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:46:24 by recherra          #+#    #+#             */
/*   Updated: 2024/09/24 19:23:42 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	env(t_env *envs, t_cmd *cmd)
{
	t_env	*curr;

	curr = envs;
	if (cmd && cmd->args[1])
		return (1);
	curr = curr->next;
	while (curr)
	{
		if (!curr->in_export)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}
