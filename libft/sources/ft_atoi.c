/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:40:20 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/03 17:22:36 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <limits.h>

int	ft_atoi(const char *str, int *error)
{
	int		neg;
	long	number;

	number = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if ((*str) == 43 || *str == 45)
	{
		if (*(str++) == 45)
			neg = -1;
	}
	while (*str >= 48 && *str <= 57)
	{
		if ((neg == 1 && (number > (INT_MAX - (*str - 48)) / 10)) || (neg == -1
				&& (number > (2147483648 - (*str - 48)) / 10)))
		{
			*error = -1;
		}
		number = number * 10 + (*str - 48);
		str++;
	}
	return ((number * neg));
}
