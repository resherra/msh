/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:22:03 by recherra          #+#    #+#             */
/*   Updated: 2024/09/21 00:48:24 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int    ft_exit(t_cmd *cmd)
{
	int state;

	state = 0;
	if (cmd && cmd->args[1] && cmd->args[2])
	{
		printf("too many arguments\n");
		return (1);
	}
	if (cmd && (cmd)->cmd && (cmd)->args[1])
		state = ft_atoi((cmd)->args[1]);
	printf("exit\n");
	exit(state % 256);
}