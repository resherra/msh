/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:06:59 by recherra          #+#    #+#             */
/*   Updated: 2024/08/05 12:07:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void    export(t_env *envs)
{
    t_env *curr;

    curr = envs;
    while (curr)
    {
        printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
        curr = curr->next;
    }
}