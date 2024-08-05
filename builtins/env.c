/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:46:24 by recherra          #+#    #+#             */
/*   Updated: 2024/08/05 11:46:25 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void env(t_env *envs)
{
    t_env *curr = envs;

    while (curr)
    {
        if (!curr->in_export)
            printf("%s=%s\n", curr->key, curr->value);
        curr = curr->next;
    }
}