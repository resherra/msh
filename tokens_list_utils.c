/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:45:45 by recherra          #+#    #+#             */
/*   Updated: 2024/07/25 08:45:47 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_token	*lst_new(char *str, t_type type, t_state state)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = type;
	new->state = state;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_add_back(t_token **head, t_token *node)
{
	t_token	*curr;

	if (!head)
		return ;
	if (!(*head))
	{
		*head = node;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
}
