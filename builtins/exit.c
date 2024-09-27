/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/27 20:43:59 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	ft_exit(t_cmd *cmd, char *exit_state)
{
	int	state;
	int	i;

	i = 0;
	state = ft_atoi(exit_state);
	printf("exit\n");
	if (cmd && cmd->args[1])
	{
		while (cmd->args[1][i] >= '0' && cmd->args[1][i] <= '9')
			i++;
		if (cmd->args[1][i] != 0)
		{
			printf("exit : %s: numeric argument required \n", cmd->args[1]);
			exit(255);
		}
	}
	if (cmd && cmd->args[1] && cmd->args[2])
	{
		printf("too many arguments\n");
		return (1);
	}
	if (cmd && (cmd)->cmd && (cmd)->args[1])
		state = ft_atoi((cmd)->args[1]);
	exit(state % 256);
}
