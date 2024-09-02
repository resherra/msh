/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:59:46 by recherra          #+#    #+#             */
/*   Updated: 2024/09/02 16:00:06 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(char *str1, char *str2)
{
    if (!str1 || !str2)
        return -1;
    while (*str1 && *str2 && *str1 == *str2)
    {
        str2++;
        str1++;
    }
    if (*str1 > *str2)
        return (1);
    else if (*str1 < *str2)
        return (-1);
    return (0);
}