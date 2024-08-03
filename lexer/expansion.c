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

#include "../init.h"

static int	single_dollar(t_token *var, int len)
{
	char	*tmp;

	if (len == 1)
	{
		tmp = var->str;
		var->str = ft_strdup("$");
		free(tmp);
		return (1);
	}
	return (0);
}

void	expansion(t_token *var, t_env *envs)
{
	t_env	*curr;
	int		len;
	char	*tmp;

	curr = envs;
	len = ft_strlen(var->str);
	if (single_dollar(var, len))
		return ;
	while (curr)
	{
		if (!ft_strncmp(var->str + 1, curr->key, len - 1))
		{
			tmp = var->str;
			var->str = curr->value;
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
	tmp = var->str;
	var->str = ft_strdup("");
	free(tmp);
	var->type = WORD;
}
