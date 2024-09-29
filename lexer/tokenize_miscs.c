/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_miscs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:28:19 by recherra          #+#    #+#             */
/*   Updated: 2024/08/02 19:28:20 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	skip_spaces(char *str, t_tokenizer_vars *vars)
{
	while ((str[vars->i] >= 9 && str[vars->i] <= 13) || str[vars->i] == ' ')
	    vars->i++;
}

t_token	*get_last_node(t_token **head)
{
	t_token	*curr;

	curr = *head;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}
