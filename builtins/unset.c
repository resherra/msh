/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:46:53 by recherra          #+#    #+#             */
/*   Updated: 2024/08/16 15:46:02 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void    func(void *content)
{
    free(content);
}

void    unset(t_env **envs, char **vars)
{
    int i = 1;
    t_env *curr;
    t_env *prev;

    while (vars[i])
    {
        curr = *envs;
        prev = curr;
        while (curr)
        {
            if (!strcmp(vars[i], curr->key))
            {   
                if (!strcmp(vars[i], (*envs)->key))
                    *envs = curr->next;
                else
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