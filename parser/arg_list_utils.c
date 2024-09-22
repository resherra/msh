/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:38:06 by recherra          #+#    #+#             */
/*   Updated: 2024/08/10 14:38:09 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_args	*new_arg(char *str)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		exit(1);
	new->str = ft_strtrim(str, "\x03");
	new->next = NULL;
	free(str);
	return (new);
}

void	arg_add_front(t_args **lst, t_args *new)
{
	if (!lst)
		return ;
	if (*lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}

void	arg_add_back(t_args **args, t_args *new)
{
	t_args	*curr;

	if (!args)
		return ;
	if (!(*args))
	{
		*args = new;
		return ;
	}
	curr = *args;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
