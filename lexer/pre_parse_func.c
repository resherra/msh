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

static void	join(t_token **curr, char **str)
{
	char *tmp;
	while ((*curr) && (*curr)->type != SPACE)
	{
		if (ft_strlen((*curr)->str) == 1)
		{
			if (((*curr)->type == ENV && (*curr)->state == GENERAL)
			    && (*curr)->next && ((*curr)->next->type == D_QUOTE
			                         || (*curr)->next->type == S_QUOTE))
			{
				*curr = (*curr)->next;
				continue ;
			}
		}
		if ((*curr)->type == D_QUOTE || (*curr)->type == S_QUOTE)
		{
			*curr = (*curr)->next;
			continue ;
		}
		tmp = *str;
		*str = ft_strjoin(*str, (*curr)->str);
		free(tmp);
		*curr = (*curr)->next;
	}
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
		join(&curr, &str);
		if (str)
		{
			node = lst_new(str, WORD, GENERAL);
			lst_add_back(new, node);
		}
		if (curr)
			curr = curr->next;
	}
}