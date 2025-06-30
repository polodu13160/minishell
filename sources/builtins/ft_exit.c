/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/30 20:37:01 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"

int	check_arg_exit(char **str, t_minishell *minishell, int i, t_pip *exec)
{
	if (!str[i + 1])
	{
		minishell->return_command = 0;
		free_exit(minishell->tokens, minishell, exec, 0);
	}
	if (str[i + 1] && str[i + 2])
	{
		ft_putendl_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	check_exit_numeric(char **str, int i, int *sign)
{
	int	x;

	x = 0;
	*sign = 0;
	while (str[i + 1][x])
	{
		if (str[i + 1][x] == '-')
			(*sign)++;
		else if (str[i + 1][x] < '0' || str[i + 1][x] > '9')
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (2);
		}
		if (*sign > 1)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (2);
		}
		x++;
	}
	return (0);
}

int	ft_exit(char **str, t_minishell *minishell, int i, t_pip *exec)
{
	int			error;
	int			sign;
	signed long long value;

	error = 0;
	if (check_arg_exit(str, minishell, i, exec) == 1)
		return 1;
	if (check_exit_numeric(str, i, &sign) == 2)
	{
		minishell->return_command = 2;
		free_exit(NULL, minishell, exec, 0);
		return 2;
	}
	value = ft_atoll(str[i + 1], &error);
	if (error)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		minishell->return_command = 2;
		free_exit(minishell->tokens, minishell, exec, 0);
		// je sais pas 
	}
	// if (sign)
	// 	value = 256 - value;
	if (value > 255)
	 	value = value % 256;
	minishell->return_command = value;
	free_exit(minishell->tokens, minishell, exec, 0);
	return 0;
}
