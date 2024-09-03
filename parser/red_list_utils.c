/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:38:54 by recherra          #+#    #+#             */
/*   Updated: 2024/08/10 14:38:58 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_red	*lst_new_red(t_type red_type, char *red_file, bool expanded)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		exit(1);
	new->red_type = red_type;
	new->red_file = red_file;
	new->is_ambegious = false;
	new->expanded = expanded;
	new->next = NULL;
	return (new);
}

void	red_add_back(t_red **redirections, t_red *new)
{
	t_red	*curr;

	if (!redirections)
		return ;
	if (!(*redirections))
	{
		*redirections = new;
		return ;
	}
	curr = *redirections;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
