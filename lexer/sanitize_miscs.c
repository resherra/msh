/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_miscs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:20:59 by recherra          #+#    #+#             */
/*   Updated: 2024/09/03 18:21:09 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	handle_single_dollar(t_token **curr)
{
	if (ft_strlen((*curr)->str) == 1)
	{
		if (((*curr)->type == ENV && (*curr)->state == GENERAL) && (*curr)->next
			&& ((*curr)->next->type == D_QUOTE
				|| (*curr)->next->type == S_QUOTE))
		{
			return (1);
		}
	}
	return (0);
}

int	join_check(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTE || token->type == D_QUOTE
		|| token->type == ENV || (token->type == SPACES
			&& token->state == IN_DOUBLE_Q))
		return (1);
	return (0);
}
