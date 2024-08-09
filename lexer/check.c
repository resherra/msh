/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:25:48 by recherra          #+#    #+#             */
/*   Updated: 2024/08/02 19:25:57 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	check_operator(char *str, int i)
{
	if (*(str + i) == ' ')
		return (SPACES);
	else if (*(str + i) == '|')
		return (PIPE);
	else if (*(str + i) == '$')
		return (ENV);
	else if (*(str + i) == '\'')
		return (S_QUOTE);
	else if (*(str + i) == '\"')
		return (D_QUOTE);
	else if (*(str + i) == '>')
	{
		if (!ft_strncmp(">>", str + i, 2))
			return (RED_APP);
		return (RED_OUT);
	}
	else if (*(str + i) == '<')
	{
		if (!ft_strncmp("<<", str + i, 2))
			return (HERE_DOC);
		return (RED_IN);
	}
	return (WORD);
}

int	check(char *str, int tmp)
{
	if (check_operator(str, tmp) == ENV && (check_operator(str, tmp
				+ 1) == D_QUOTE || check_operator(str, tmp + 1) == S_QUOTE))
	{
		return (1);
	}
	return (0);
}
