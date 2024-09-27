/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_miscs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:39 by recherra          #+#    #+#             */
/*   Updated: 2024/09/27 01:46:20 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_all(t_data *data)
{
	data->envs = NULL;
	data->envp = NULL;
	data->cmd = NULL;
	data->head = NULL;
	data->paths = NULL;
	data->pre = NULL;
	data->str = NULL;
}

void	clear_all(t_data *data)
{
	lstclear(&data->head);
	lstclear(&data->pre);
	add_history(data->str);
	free(data->str);
}
