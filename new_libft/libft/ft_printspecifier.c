/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printspecifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:08:08 by antbonin          #+#    #+#             */
/*   Updated: 2025/02/10 15:45:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ressource/libft.h"
#include <stdlib.h>

int	ft_printdecimal(long int n)
{
	char	*str;
	int		count;

	count = 0;
	str = "0123456789";
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n < 10)
		return (count + write(1, &str[n], 1));
	else
		return (count + ft_printdecimal(n / 10) + ft_printdecimal(n % 10));
}

int	ft_printhexa(unsigned long int n, char hex)
{
	char	*str;

	if (hex == 'x')
		str = HEXA_MIN;
	else
		str = HEXA_CAPS;
	if (n < 16)
		return (write(1, &str[n], 1));
	else
	{
		return (ft_printhexa(n / 16, hex) + ft_printhexa(n % 16, hex));
	}
}

int	ft_printpointer(void *s)
{
	if (!s)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_printhexa((unsigned long int)s, 'x'));
}
