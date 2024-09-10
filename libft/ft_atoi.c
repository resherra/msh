/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:43:53 by recherra          #+#    #+#             */
/*   Updated: 2024/09/09 16:15:50 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*(str + 1) == '+' || *(str + 1) == '-')
			return (0);
		else if (*str == '-')
			sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += (*str - 48);
		str++;
	}
	if (sign == 1)
		return (-number);
	return (number);
}
