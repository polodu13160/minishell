/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:15:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/21 18:07:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "stdlib.h"

size_t	ft_strlen_gnl(const char *str)
{
	const char	*s = str;

	while (*s)
		s++;
	return (s - str);
}

char	*ft_strdup_gnl(const char *src)
{
	char	*dest;
	size_t	line_length;
	size_t	i;

	i = 0;
	line_length = 0;
	while (src[line_length] && src[line_length] != '\n')
		line_length++;
	if (src[line_length] == '\n')
		line_length++;
	dest = malloc(line_length + 1);
	if (!dest)
		return (NULL);
	while (i < line_length)
	{
		dest[i] = src[i];
		i++;
	}
	dest[line_length] = '\0';
	return (dest);
}

static size_t	ft_strlcpy_gnl(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen_gnl(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[size - 1] = '\0';
	return (src_len);
}

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	len_s1 = ft_strlen_gnl(s1);
	len_s2 = 0;
	while (s2[len_s2] && s2[len_s2] != '\n')
		len_s2++;
	if (s2[len_s2] == '\n')
		len_s2++;
	str = malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (free(s1), NULL);
	ft_strlcpy_gnl(str, s1, len_s1 + 1);
	ft_strlcpy_gnl(str + len_s1, s2, len_s2 + 1);
	free(s1);
	return (str);
}
