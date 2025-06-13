/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/10 18:13:05 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

int	check_arg_exit(char **str, t_minishell *minishell, int i, t_pip *exec)
{
	if (!str[i + 1])
	{
		minishell->code_error = 0;
		free_exit(minishell->tokens, minishell, exec);
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

void	ft_exit(char **str, t_minishell *minishell, int i, t_pip *exec)
{
	int			error;
	int			sign;
	long long	value;

	error = 0;
	if (check_arg_exit(str, minishell, i, exec) == 1)
		return ;
	if (check_exit_numeric(str, i, &sign) == 2)
	{
		minishell->code_error = 2;
		free_exit(NULL, minishell, exec);
	}
	value = ft_atoll(str[i + 1], &error);
	if (error)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		minishell->code_error = 2;
		free_exit(minishell->tokens, minishell, exec);
	}
	if (sign)
		value = 256 - value;
	else if (value > 255)
		value = value % 256;
	minishell->code_error = value;
	free_exit(minishell->tokens, minishell, exec);
}
