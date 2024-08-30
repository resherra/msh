/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:46:24 by recherra          #+#    #+#             */
/*   Updated: 2024/08/28 20:54:53 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

int env(t_env *envs)
{
    t_env *curr = envs;

    while (curr)
    {
        
        if (!curr->in_export)
            printf("%s=%s\n", curr->key, curr->value);
        curr = curr->next;
    }
    return (0);
}