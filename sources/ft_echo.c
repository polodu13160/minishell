/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:13:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/26 15:55:09 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "unistd.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		if (str[2] == 'n')
		{
			i = 2;
			while (str[i])
			{
				if (str[i] == 'n')
					i++;
				else
					return (1);
			}
		}
	}
	else
		return (1);
	return (0);
}

int	ft_echo(char **str, int start)
{
	int	i;
	int	no_newline;

	(void)start;
	i = 0;
	no_newline = 0;
	if (str[1] && !check_arg(str[1]))
	{
		no_newline = 1;
		i++;
		while (!check_arg(str[i + 1]))
			i++;
	}
	i++;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
