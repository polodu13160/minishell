/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:new_libft/libft/ft_print_hexa.c
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
========
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
>>>>>>>> origin/parsing:new_libft/libft/ft_strcpy.c
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:new_libft/libft/ft_print_hexa.c
/*   Created: 2024/12/03 23:00:24 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 06:27:03 by pde-petr         ###   ########.fr       */
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
========
/*   Created: 2025/05/18 19:55:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/18 19:55:58 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
>>>>>>>> origin/parsing:new_libft/libft/ft_strcpy.c
}
