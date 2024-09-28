/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_func_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:23:44 by recherra          #+#    #+#             */
/*   Updated: 2024/09/28 19:23:58 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	sticked_quotes_check(t_token *curr)
{
	if ((curr->type == D_QUOTE && curr->next && curr->next->type == D_QUOTE)
		|| (curr->type == S_QUOTE && curr->next && curr->next->type == S_QUOTE))
		return (1);
	return (0);
}

int	expanded_empty_check(t_token *curr, t_flags *flags)
{
	if (curr->type == SPACES && curr->state == IN_DOUBLE_Q
		&& flags->expanded_empty == false)
		return (1);
	return (0);
}

t_token	*create_node(char *str, t_flags flags)
{
	t_token	*node;

	if (!(*str))
	{
		if (flags.expanded_empty && !flags.quotes_stick)
			node = lst_new(str, SPACES, IN_DOUBLE_Q);
		else
			node = lst_new(str, WORD, GENERAL);
	}
	else
		node = lst_new(str, WORD, GENERAL);
	return (node);
}
