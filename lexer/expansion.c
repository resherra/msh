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
		tmp = NULL;
		return (1);
	}
	return (0);
}

static void	check_dq_flag(t_token *var, t_env *curr, bool in_double_quotes)
{
	char	*trimmed;

	if (in_double_quotes)
	{
		trimmed = ft_strtrim(curr->value, "\x03");
		var->str = trimmed;
	}
	else
		var->str = ft_strdup(curr->value);
}

void	change_empty_type(t_token *var, bool *joe)
{
	*joe = true;
	var->str = ft_strdup("");
	var->type = SPACES;
	var->state = IN_DOUBLE_Q;
}

int	find_var(t_token *var, t_env *curr, bool in_double_quotes)
{
	char	*tmp;

	if (!ft_strcmp(var->str + 1, curr->key))
	{
		tmp = var->str;
		check_dq_flag(var, curr, in_double_quotes);
		free(tmp);
		return (1);
	}
	return (0);
}

void	expansion(t_token *var, t_env *envs, bool in_double_quotes)
{
	t_env	*curr;
	int		len;
	bool	joe;
	char	*tmp;

	joe = false;
	curr = envs;
	len = ft_strlen(var->str);
	if (single_dollar(var, len))
		return ;
	while (curr)
	{
		if (find_var(var, curr, in_double_quotes))
			return ;
		curr = curr->next;
	}
	tmp = var->str;
	if (in_double_quotes)
		var->str = ft_strdup("");
	else
		change_empty_type(var, &joe);
	free(tmp);
	if (!joe)
		var->type = WORD;
}
