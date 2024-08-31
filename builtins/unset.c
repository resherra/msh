/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:46:53 by recherra          #+#    #+#             */
/*   Updated: 2024/08/30 16:25:10 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void    func(void *content)
{
    free(content);
}

int    unset(t_env **envs, char **vars)
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
            if (!ft_strcmp(vars[i], curr->key))
            {   
                if (!ft_strcmp(vars[i], (*envs)->key))
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
    return (0);
}