/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:59:38 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/16 15:11:20 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa(int fd, unsigned long int hexa, char type)
{
	char	*hexa_tab;

	if (type == 'x')
		hexa_tab = HEXAMIN;
	else
		hexa_tab = HEXACAPS;
	if (hexa < 16)
		return (write(1, &hexa_tab[hexa], 1));
	else
		return (ft_printhexa(fd, hexa / 16, type) + write(fd, &hexa_tab[hexa
					% 16], 1));
}
