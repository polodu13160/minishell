/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:44:21 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/20 22:17:00 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count;

	count = 0;
	va_start(arg, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == ' ' || !*(format + 1)))
		{
			return (-1);
		}
		else if (*format == '%')
			count += ft_printf_format(1, *(++format), arg);
		else
			count += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(arg);
	return (count);
}
