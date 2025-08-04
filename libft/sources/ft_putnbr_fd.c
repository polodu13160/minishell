/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:07:35 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/20 22:10:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"

int	ft_putnbr_fd(long int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (ft_putstr_fd("-2147483648", fd));
	}
	else
	{
		if (n < 0)
		{
			count += ft_putchar_fd(45, fd);
			n = -n;
		}
		if (n >= 10)
			count += ft_putnbr_fd(n / 10, fd);
		count += (ft_putchar_fd(n % 10 + 48, fd));
	}
	return (count);
}
