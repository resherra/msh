/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:10:05 by recherra          #+#    #+#             */
/*   Updated: 2024/08/28 20:22:21 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static t_token	*double_quote_check(t_token *curr, bool *flag, t_env *env)
{
	if (curr->type == D_QUOTE)
	{
		*flag = true;
		curr = curr->next;
		while (curr && curr->type != D_QUOTE)
		{
			if (curr->type == ENV)
				expansion(curr, env, true);
			else
				curr->type = WORD;
			curr->state = IN_DOUBLE_Q;
			curr = curr->next;
		}
		if (curr)
			*flag = false;
	}
	return (curr);
}

static t_token	*single_quote_check(t_token *curr, bool *flag)
{
	if (curr && curr->type == S_QUOTE)
	{
		*flag = true;
		curr = curr->next;
		while (curr && curr->type != S_QUOTE)
		{
			curr->type = WORD;
			curr->state = IN_S_QUOTE;
			curr = curr->next;
		}
		if (curr)
			*flag = false;
	}
	return (curr);
}

int	set_state(t_token *head, t_env *env)
{
	t_token	*curr;
	bool	doub_quote_flag;
	bool	sing_quote_flag;

	curr = head;
	doub_quote_flag = false;
	sing_quote_flag = false;
	while (curr)
	{
		curr = double_quote_check(curr, &doub_quote_flag, env);
		curr = single_quote_check(curr, &sing_quote_flag);
		if (curr && curr->type == ENV)
			expansion(curr, env, false);
		if (doub_quote_flag == true || sing_quote_flag == true)
			return (1);
		curr = curr->next;
	}
	return (0);
}
