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

void	quote_case_wrapper(bool after_heredoc, bool *flag, t_token **curr,
		char **str)
{
	if (after_heredoc)
		*flag = true;
	safejoin(curr, str, true);
}

static t_token	*join(t_token *curr, char **str, bool after_heredoc, bool *flag)
{
	while (curr && join_check(curr))
	{
		if (handle_single_dollar(&curr))
			continue ;
		if (curr->type == D_QUOTE && curr->next && curr->next->type == D_QUOTE)
		{
			quote_case_wrapper(after_heredoc, flag, &curr, str);
			continue ;
		}
		else if (curr->type == S_QUOTE && curr->next
				&& curr->next->type == S_QUOTE)
		{
			quote_case_wrapper(after_heredoc, flag, &curr, str);
			continue ;
		}
		else if (curr->type == D_QUOTE || curr->type == S_QUOTE)
		{
			if (after_heredoc)
				*flag = true;
			curr = curr->next;
			continue ;
		}
		safejoin(&curr, str, false);
	}
	return (curr);
}

static t_token	*handle_ope_and_delimiter(t_token *curr, t_token **new,
		char **str, bool *flag)
{
	t_token	*node;
	t_token	*tmp;

	tmp = NULL;
	node = lst_new(ft_strdup(curr->str), curr->type, curr->state);
	lst_add_back(new, node);
	if (curr->type == HERE_DOC)
	{
		curr = curr->next;
		while (curr && curr->type == SPACES)
			curr = curr->next;
		tmp = curr;
		curr = join(curr, str, true, flag);
		if (*str)
		{
			if (*flag)
				node = lst_new(*str, WORD, IN_DOUBLE_Q);
			else
				node = lst_new(*str, WORD, GENERAL);
			lst_add_back(new, node);
		}
	}
	if (curr && tmp == curr)
		special_case(curr, new, &node);
	return (curr);
}

void	sanitize(t_token *head, t_token **new)
{
	t_token	*curr;
	t_token	*node;
	char	*str;
	bool	flag;

	flag = false;
	curr = head;
	while (curr)
	{
		str = NULL;
		curr = join(curr, &str, false, &flag);
		if (str)
		{
			node = lst_new(str, WORD, GENERAL);
			lst_add_back(new, node);
		}
		if (curr && curr->type != SPACES)
			curr = handle_ope_and_delimiter(curr, new, &str, &flag);
		if (curr)
			curr = curr->next;
	}
}
