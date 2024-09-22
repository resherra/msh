/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:46:53 by recherra          #+#    #+#             */
/*   Updated: 2024/09/22 02:38:20 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../init.h"

void    func(void *content)
{
    free(content);
}
int check_identifier(char *str)
{
	int var_len;

	var_len = 0;
	if (str[var_len] != '_' && !ft_isalpha(str[var_len++]))
	{
		printf("unset: `%s' : not a valid identifier\n", str);	
		return (1);
	}
	while (str[var_len] != 0 && (ft_isalnum(str[var_len]) || str[var_len] == '_'))
    {
		var_len++;
    }
	if (str[var_len] == 0)
		return (0);
	printf("unset: `%s' : not a valid identifier\n", str);	
	return(1);
}

int   unset(t_env **envs, char **vars)
{
    int i = 1;
    int state;
    t_env *curr;
    t_env *prev;

    state = 0;
    while (vars[i])
    {
        curr = *envs;
        prev = curr;
        state += check_identifier(vars[i]);
        while (curr)
        {
            if (!ft_strcmp(vars[i], curr->key))
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
    return (state > 0);
}
