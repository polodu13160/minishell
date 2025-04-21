/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:24:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/21 18:07:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0)
		return (ptr = malloc(0));
	if (size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
