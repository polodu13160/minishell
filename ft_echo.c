/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:13:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "unistd.h"

void	print_echo(char **av, int start, int nl_flag)
{
	int	i;
	int	j;

	i = start;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			write(1, &av[i][j], 1);
			j++;
		}
		if (av[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl_flag)
		write(1, "\n", 1);
}

int	ft_echo(int ac, char **av)
{
	int	flag;

	if (ac == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = 1;
	if (av[1][0] == '-' && av[1][1] == 'n')
	{
		flag = 2;
		if (ac == 2)
			return (0);
	}
	print_echo(av, flag, (flag == 1));
	return (0);
}
