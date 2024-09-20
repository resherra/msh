/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:22:03 by recherra          #+#    #+#             */
/*   Updated: 2024/09/20 13:10:32 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void    ft_exit(t_cmd *cmd, t_env **env)
{
	int state;

	if (cmd->args[1] && cmd->args[2])
	{
		(*env)->value = ft_strdup("1");
		//printf("%s==\n", env->value);
		printf("tpp many arguments\n");
		return ;
	}
	state = 0;
	if (cmd && (cmd)->cmd && (cmd)->args[1])
		state = ft_atoi((cmd)->args[1]);
	printf("exit\n");
	exit(state % 256);
}