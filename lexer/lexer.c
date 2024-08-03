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

void	lexer(char *str, t_token **head, t_env *env, t_token **pre)
{
	tokenize(str, head);
	if (set_state(*head, env))
	{
		printf("syntax error\n");
		exit(1);
	}
	sanitize(*head, pre);
}
