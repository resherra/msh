/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/29 21:44:48 by schakkou         ###   ########.fr       */
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
