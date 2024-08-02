/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_content_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:17:01 by recherra          #+#    #+#             */
/*   Updated: 2024/08/02 17:17:03 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

char	*char_to_str(char c)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = 0;
	return (new);
}

char	*double_to_str(char *str, int i)
{
	char	*new;

	new = malloc(sizeof(char) * 3);
	if (!new)
		return (NULL);
	new[0] = *(str + i);
	new[1] = *(str + i + 1);
	new[2] = 0;
	return (new);
}
