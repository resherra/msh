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

int check_if_alpha(char *str)
{
    int i = 0;

    if (str[i])
    {
        if (ft_isalpha(str[i]) == 0)
            return 0;
    }
    i++;
    while (str[i])
    {
        if (ft_isalnum(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}

void    treat(t_env **envs, char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    char *key;
    char *value;

    while (str[i] && str[i] != '=')
        i++;
    key = ft_substr(str, 0, i);
    if (!check_if_alpha(key))
    {
        printf("msh: export: `%s': not a valid identifier\n", key);
        return;
    }
    if (!str[i])
    {
        value = ft_strdup("");
        t_env *env =  new_env(key, value);
        env->in_export = true;
        env_addback(envs, env);
    } else
    {
        value = ft_substr(str, i + 1, len);
        t_env *env = new_env(key, value);
        env_addback(envs, env);
    }
}


void    export(t_env **envs, t_cmd *cmd)
{
    t_env *curr = NULL;
    int i = 0;

    if (cmd->args_lst_size == 1)
    {
        curr = *envs;
        while (curr)
        {
            printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
            curr = curr->next;
        }
        return;
    }
    i++;
    while (cmd->args[i])
    {
        treat(envs, cmd->args[i]);
        i++;
    }
}