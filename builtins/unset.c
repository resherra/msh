/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:46:53 by recherra          #+#    #+#             */
/*   Updated: 2024/08/05 10:46:55 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void    func(void *content)
{
    free(content);
}

void    unset(t_env *envs, char **vars)
{
    int i = 0;
    t_env *curr;
    t_env *prev;

    while (vars[i])
    {
        prev = NULL;
        curr = envs;
        while (curr)
        {
            if (!strcmp(vars[i], curr->key))
            {
                prev->next = curr->next;
                env_delone(curr, func);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        i++;
    }
}