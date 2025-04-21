/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:51:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/21 18:07:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"

int	ft_specifier(char specifier, va_list ap)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_printdecimal(va_arg(ap, int)));
	else if (specifier == 'u')
		return (ft_printdecimal(va_arg(ap, unsigned int)));
	else if (specifier == 'x')
		return (ft_printhexa(va_arg(ap, unsigned int), specifier));
	else if (specifier == 'X')
		return (ft_printhexa(va_arg(ap, unsigned int), specifier));
	else if (specifier == 'p')
		return (ft_printpointer(va_arg(ap, void *)));
	else
		return (ft_putchar_fd(specifier, 1));
}
