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
	if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_APP)
		return 1;
	return 0;
}

void	print_syntax_error(char *token)
{
	printf("msh: syntax error near unexpected token `%s'\n", token);
	exit(1);
}

void	syntax_check(t_token *pre)
{
	t_token *curr = pre;

	while (curr)
	{
		if (check_redirections(curr))
		{
			if (!curr->next || curr->next->type != WORD)
				print_syntax_error(curr->str);
		}
		if (curr->type == PIPE)
		{
			if (!curr->prev || curr->prev->type != WORD)
				print_syntax_error(curr->str);
			if (!curr->next || (curr->next->type != WORD && !check_redirections(curr->next)))
				print_syntax_error(curr->str);
		}
		curr = curr->next;
	}
}


void	lexer(char *str, t_token **head, t_env *env, t_token **pre)
{
	tokenize(str, head);
	if (set_state(*head, env))
	{
		printf("Syntax Error: unclosed quotes\n");
		exit(1);
	}
	sanitize(*head, pre);
	syntax_check(*pre);
}
