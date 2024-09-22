/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnvp_utilc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:42:07 by recherra          #+#    #+#             */
/*   Updated: 2024/09/22 18:42:13 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

char **lst_to_envp(t_env *envs)
{
    int i = 0;
    t_env *curr = envs;
    while (curr)
    {
        i++;
        curr = curr->next;
    }
    char **res = malloc(sizeof(char *) * (i + 1));
    if (!res)
        exit(1);

    i = 0;
    t_env *new = envs;
    new = new->next;
    while (new)
    {
        if (new->in_export == FALSE)
        {
            char *trimmed_value = ft_strtrim(new->value, "\x03");
            char *full_key = ft_strjoin(new->key, "=");
            res[i++] = ft_strjoin(full_key, trimmed_value);
            free(trimmed_value);
            free(full_key);
        }
        new = new->next;
    }
    res[i] = 0;
    return res;
}