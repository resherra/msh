/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:38:54 by recherra          #+#    #+#             */
/*   Updated: 2024/08/10 14:38:58 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_red *lst_new_red(t_type red_type, char *red_file)
{
    t_red *new = malloc(sizeof(t_red));
    new->red_type = red_type;
    new->red_file = red_file;
    new->next = NULL;
    return new;
}

void    red_add_back(t_red **redirections, t_red *new)
{
    if (!redirections)
        return;
    if (!(*redirections))
    {
        *redirections = new;
        return;
    }

    t_red *curr = *redirections;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}