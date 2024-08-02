/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:13:30 by recherra          #+#    #+#             */
/*   Updated: 2024/08/02 17:13:31 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "init.h"

void	expansion(t_token *var, t_env *envs)
{
	t_env	*curr;
	int		len;

	curr = envs;
	len = ft_strlen(var->str);
	if (len == 1)
	{
		var->str = ft_strdup("$");
		return ;
	}
	while (curr)
	{
		if (!ft_strncmp(var->str + 1, curr->key, len - 1))
		{
			var->str = curr->value;
			return ;
		}
		curr = curr->next;
	}
	var->str = ft_strdup("");
	var->type = WORD;
}