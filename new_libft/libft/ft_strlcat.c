/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:45:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/02/10 15:45:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ressource/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	while (dst[dst_len] && dst_len < n)
		dst_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (n <= dst_len)
		return (n + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < (n - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
