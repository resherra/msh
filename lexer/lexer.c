/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:45:31 by recherra          #+#    #+#             */
/*   Updated: 2024/08/03 09:45:33 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	check_redirections(t_token *curr)
{
	if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_APP
		|| curr->type == HERE_DOC)
		return (1);
	return (0);
}

int	print_syntax_error(char *token)
{
	ft_putstr_fd("msh: syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

int	syntax_check(t_token *pre)
{
	t_token	*curr;

	curr = pre;
	while (curr)
	{
		if (check_redirections(curr))
		{
			if (!curr->next || (curr->next->type != WORD && curr->next->type != SPACES))
            {
                return (print_syntax_error(curr->str));
            }
		}
		if (curr->type == PIPE)
		{
			if (!curr->prev || curr->prev->type != WORD)
				return (print_syntax_error(curr->str));
			if (!curr->next || (curr->next->type != WORD
					&& !check_redirections(curr->next)))
				return (print_syntax_error(curr->str));
		}
		curr = curr->next;
	}
	return (0);
}

int	lexer(char *str, t_token **head, t_env *env, t_token **pre)
{
	tokenize(str, head);
    if (set_state(*head, env))
	{
		printf("Syntax Error: unclosed quotes\n");
		return (1);
	}
    sanitize(*head, pre);
    if (syntax_check(*pre))
		return (1);
	return (0);
}
