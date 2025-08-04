/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:51:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 06:44:25 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdarg.h>

static int	check_null_pointer(int fd, void *pointer)
{
	if (!pointer)
		return (write(fd, "(nil)", 5));
	return (write(fd, "0x", 2) + ft_printhexa(fd, (unsigned long int)pointer,
			'x'));
}

static int	check_null_string(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (ft_putstr_fd(str, fd));
}

int	ft_printf_format(int fd, char format, va_list arg)
{
	if (format == 'c')
		return (ft_putchar_fd(va_arg(arg, int), fd));
	if (format == 's')
		return (check_null_string(fd, va_arg(arg, char *)));
	if (format == 'i' || format == 'd')
		return (ft_putnbr_fd(va_arg(arg, int), fd));
	if (format == 'x')
		return (ft_printhexa(fd, va_arg(arg, unsigned int), format));
	if (format == 'X')
		return (ft_printhexa(fd, va_arg(arg, unsigned int), format));
	if (format == 'u')
		return (ft_putnbr_fd(va_arg(arg, unsigned int), fd));
	if (format == '%')
		return (write(fd, "%", 1));
	if (format == 'p')
		return (check_null_pointer(fd, va_arg(arg, void *)));
	return (write(fd, &format, 1));
}
