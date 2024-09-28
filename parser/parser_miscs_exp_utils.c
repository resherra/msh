/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_miscs_exp_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:46:01 by recherra          #+#    #+#             */
/*   Updated: 2024/09/28 19:46:15 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	all_space_var(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	if (!ft_strcmp(tmp, "\x03"))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
