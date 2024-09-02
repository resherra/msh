/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:19:34 by recherra          #+#    #+#             */
/*   Updated: 2024/08/02 19:19:35 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static int	join_check(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTE || token->type == D_QUOTE
		|| token->type == ENV)
		return (1);
	return (0);
}

void	safejoin(t_token **curr, char **str, bool is_quotes_case)
{
	char	*tmp;

	tmp = *str;
	if (is_quotes_case)
		*str = ft_strjoin(*str, "");
	else
		*str = ft_strjoin(*str, (*curr)->str);
	free(tmp);
	*curr = (*curr)->next;
}

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

static t_token	*join(t_token *curr, char **str)
{
	while (curr && join_check(curr))
	{
		if (handle_single_dollar(&curr))
			continue ;
		if (curr->type == D_QUOTE && curr->next && curr->next->type == D_QUOTE)
		{
			safejoin(&curr, str, true);
			continue ;
		}
		else if (curr->type == S_QUOTE && curr->next
				&& curr->next->type == S_QUOTE)
		{
			safejoin(&curr, str, true);
			continue ;
		}
		else if (curr->type == D_QUOTE || curr->type == S_QUOTE)
		{
			curr = curr->next;
			continue ;
		}
		safejoin(&curr, str, false);
	}
	return (curr);
}

void	sanitize(t_token *head, t_token **new)
{
	t_token	*curr;
	t_token	*node;
	char	*str;

	curr = head;
	while (curr)
	{
		str = NULL;
		curr = join(curr, &str);
		if (str)
		{
			node = lst_new(str, WORD, GENERAL);
			lst_add_back(new, node);
		}
		if (curr && curr->type != SPACES)
		{
			node = lst_new(ft_strdup(curr->str), curr->type, curr->state);
			lst_add_back(new, node);
		}
		if (curr)
			curr = curr->next;
	}
}
