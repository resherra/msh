/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:38:36 by recherra          #+#    #+#             */
/*   Updated: 2024/09/18 16:26:49 by apple            ###   ########.fr       */
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
	new->
	path = NULL;
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
