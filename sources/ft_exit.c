/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 21:08:25 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

int	check_arg_exit(t_token *token, t_minishell *minishell, int i, t_pip *exec)
{
	if (!token[i + 1].value)
	{
		minishell->code_error = 0;
		free_exit(token, minishell, exec);
	}
	if (token[i + 1].value && token[i + 2].value)
	{
		ft_putendl_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	check_exit_numeric(t_token *token, int i, int *sign)
{
	int	x;

	x = 0;
	*sign = 0;
	while (token[i + 1].value[x])
	{
		if (token[i + 1].value[x] == '-')
			(*sign)++;
		else if (token[i + 1].value[x] < '0' || token[i + 1].value[x] > '9')
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

void	ft_exit(t_token *token, t_minishell *minishell, int i, t_pip *exec)
{
	int			error;
	int			sign;
	long long	value;

	error = 0;
	if (check_arg_exit(token, minishell, i, exec) == 1)
		return ;
	if (check_exit_numeric(token, i, &sign) == 2)
	{
		minishell->code_error = 2;
		free_exit(token, minishell, exec);
	}
	value = ft_atoll(token[i + 1].value, &error);
	if (error)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		minishell->code_error = 2;
		free_exit(token, minishell, exec);
	}
	if (sign)
		value = 256 - value;
	else if (value > 255)
		value = value % 256;
	minishell->code_error = value;
	free_exit(token, minishell, exec);
}
