/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:13:21 by antbonin          #+#    #+#             */
/*   Updated: 2025/02/10 15:47:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ressource/libft.h"
#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
