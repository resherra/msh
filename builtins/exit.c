/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:22:03 by recherra          #+#    #+#             */
/*   Updated: 2024/09/10 01:25:25 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void    ft_exit(t_cmd **cmd)
{
	int state;

	state = 0;
	if (*cmd && (*cmd)->cmd && (*cmd)->args[1])
		state = ft_atoi((*cmd)->args[1]);
	printf("exit\n");
	exit(state % 256);
	free_cmd_list(cmd);
}