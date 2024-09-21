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