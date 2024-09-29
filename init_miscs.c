/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_miscs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/29 21:48:15 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_all(t_data *data)
{
	data->envs = NULL;
	data->envp = NULL;
	data->cmd = NULL;
	data->head = NULL;
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
