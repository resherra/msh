/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:08:33 by recherra          #+#    #+#             */
/*   Updated: 2024/09/22 18:08:53 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	free_cmd_list(t_cmd **cmds)
{
	t_cmd	*tmp;

	if (!cmds)
		return ;
	if (*cmds)
	{
		while (*cmds)
		{
			tmp = *cmds;
			*cmds = (*cmds)->next;
			if (tmp->cmd != tmp->path)
				free(tmp->path);
			free_all(tmp);
			free(tmp);
		}
	}
	*cmds = NULL;
}

void	lstclear(t_token **head)
{
	t_token	*ne;

	if (!head || !*head)
		return ;
	while (*head)
	{
		ne = *head;
		*head = (*head)->next;
		free(ne->str);
		ne->str = NULL;
		free(ne);
		ne = NULL;
	}
	*head = NULL;
}

void	clear_args_list(t_args **head)
{
	t_args	*ne;

	if (!head)
		return ;
	if (*head)
	{
		while (*head)
		{
			ne = *head;
			*head = (*head)->next;
			free(ne->str);
			free(ne);
		}
	}
	*head = NULL;
}

void	clear_redirections(t_red **head)
{
	t_red	*ne;

	if (!head)
		return ;
	if (*head)
	{
		while (*head)
		{
			ne = *head;
			*head = (*head)->next;
			free(ne->red_file);
			free(ne);
		}
	}
	*head = NULL;
}

void	free_all(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	clear_redirections(&cmd->redirections);
	clear_args_list(&cmd->args_list);
}
