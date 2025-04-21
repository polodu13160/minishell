/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:36:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/02/10 15:45:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ressource/libft.h"

char	*ft_copy(char *str, char *str2, size_t len)
{
	while (len > 0)
	{
		len--;
		str[len] = str2[len];
	}
	return (str);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str;
	char	*str2;

	str = (char *)dst;
	str2 = (char *)src;
	i = 0;
	if (str2 < str)
		ft_copy(str, str2, len);
	else
	{
		while (i < len)
		{
			str[i] = str2[i];
			i++;
		}
	}
	return (dst);
}
