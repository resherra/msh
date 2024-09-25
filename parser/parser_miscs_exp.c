/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:05:49 by recherra          #+#    #+#             */
/*   Updated: 2024/09/14 12:05:51 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	special_case(t_token *curr, t_token **new, t_token **node)
{
	*node = lst_new(ft_strdup(curr->str), curr->type, curr->state);
	lst_add_back(new, *node);
}

char	*free_and_return(char *pre_path, char *to_return)
{
	free(pre_path);
	return (to_return);
}

void	init_vars(t_parser_vars *vars, t_token **pre)
{
	vars->arg = NULL;
	vars->new_red = NULL;
	vars->curr = *pre;
	vars->counter = 0;
}

void	count_heredoc(t_parser_vars *vars)
{
	if (vars->curr && !vars->new_cmd->is_herdc && vars->curr->type == HERE_DOC)
	{
		vars->counter++;
		vars->new_cmd->is_herdc = true;
	}
}
