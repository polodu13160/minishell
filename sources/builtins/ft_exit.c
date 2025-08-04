/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 20:47:01 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"

int	check_arg_exit(char **str, t_minishell *minishell, t_pip *exec,
		int print_exit)
{
	int	i;

	i = 0;
	if (!str[i + 1])
	{
		minishell->return_command = 0;
		free_exit(minishell->tokens, minishell, exec, print_exit);
	}
	if (str[i + 1] && str[i + 2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	check_exit_numeric(char **str, int i, int *sign, int x)
{
	int	plus_sign;

	*sign = 0;
	plus_sign = 0;
	while (str[i + 1] && str[i + 1][x])
	{
		if (str[i + 1][x] == '+')
			plus_sign++;
		if (str[i + 1][x] == '-')
			(*sign)++;
		if (str[i + 1][x] == '+' || str[i + 1][x] == '-')
			x += 0;
		else if (str[i + 1][x] < '0' || str[i + 1][x] > '9')
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (2);
		}
		if (*sign > 1 || plus_sign > 1)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (2);
		}
		x++;
	}
	return (0);
}

static void	print_error_exit(t_minishell *minishell)
{
	ft_putendl_fd("exit: numeric argument required", 2);
	minishell->return_command = 2;
}

int	check_exit(char **str, t_minishell *minishell, t_pip *exec, int print_exit)
{
	int	sign;

	sign = 0;
	if (str[1] && str[1][0] == '\0')
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		minishell->return_command = 2;
		free_exit(minishell->tokens, minishell, exec, print_exit);
	}
	if (check_exit_numeric(str, 0, &sign, 0) == 2)
	{
		minishell->return_command = 2;
		free_exit(minishell->tokens, minishell, exec, print_exit);
	}
	return (sign);
}

int	ft_exit(char **str, t_minishell *minishell, t_pip *exec, int print_exit)
{
	int					error;
	int					sign;
	signed long long	value;

	error = 0;
	sign = check_exit(str, minishell, exec, print_exit);
	if (check_arg_exit(str, minishell, exec, print_exit) == 1)
		return (1);
	value = ft_atoll(str[0 + 1], &error);
	if (error)
	{
		print_error_exit(minishell);
		free_exit(minishell->tokens, minishell, exec, print_exit);
	}
	if (sign)
		value = 256 - value;
	if (value > 255)
		value = value % 256;
	minishell->return_command = value;
	free_exit(minishell->tokens, minishell, exec, print_exit);
	return (0);
}
