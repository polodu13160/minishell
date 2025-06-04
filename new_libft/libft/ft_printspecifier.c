/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printspecifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:08:08 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 06:44:15 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdlib.h>

int	ft_printdecimal(int fd, long int n)
{
	char	*str;
	int		count;

	count = 0;
	str = "0123456789";
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	if (n < 10)
		return (count + write(fd, &str[n], 1));
	else
		return (count + ft_printdecimal(fd, n / 10) + ft_printdecimal(fd, n
				% 10));
}

int	ft_printhexa(int fd, unsigned long int n, char hex)
{
	char	*str;

	if (hex == 'x')
		str = HEXA_MIN;
	else
		str = HEXA_CAPS;
	if (n < 16)
		return (write(fd, &str[n], 1));
	else
	{
		return (ft_printhexa(fd, n / 16, hex) + ft_printhexa(fd, n % 16, hex));
	}
}

int	ft_printpointer(int fd, void *s)
{
	if (!s)
		return (write(fd, "(nil)", 5));
	return (write(fd, "0x", 2) + ft_printhexa(fd, (unsigned long int)s, 'x'));
}
