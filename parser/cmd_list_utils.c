/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:35:22 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 21:49:31 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit(1);
	new->args_list = NULL;
	new->cmd = NULL;
	new->path = NULL;
	new->args = NULL;
	new->redirections = NULL;
	new->args_lst_size = 0;
	new->nmbr_of_herdc = 0;
	new->next = NULL;
	new->is_herdc = false;
	return (new);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*curr;

	if (!cmd)
		return ;
	if (!(*cmd))
	{
		*cmd = new;
		return ;
	}
	curr = *cmd;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
