/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:38:36 by recherra          #+#    #+#             */
/*   Updated: 2024/08/10 14:38:49 by recherra         ###   ########.fr       */
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
	new->unclosed = false;
	new->next = NULL;
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
