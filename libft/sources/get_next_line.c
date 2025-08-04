/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:30:14 by pauldepetri       #+#    #+#             */
/*   Updated: 2025/04/21 18:07:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "stdlib.h"

static void	ft_bzero_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
}

int	check_end_line(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_strlcpy1(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src || !dest)
		return (0);
	if (size == 0)
		return (ft_strlen_gnl(src));
	while (src[i] && (i < (size - 1)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen_gnl(src));
}

static void	ft_next_line(char *str)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	str_len = ft_strlen(str + i);
	ft_strlcpy1(str, str + i, str_len + 1);
	ft_bzero_gnl(str + str_len);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "\0";
	ssize_t		bytes_read;
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = ft_strdup_gnl(buf);
	if (!str)
		return (NULL);
	bytes_read = 1;
	while (bytes_read && check_end_line(buf) == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_bzero_gnl(buf), free(str), NULL);
		buf[bytes_read] = '\0';
		str = ft_strjoin_gnl(str, buf);
		if (!str)
			return (NULL);
	}
	ft_next_line(buf);
	if (str[0] == '\0')
		return (free(str), NULL);
	return (str);
}
