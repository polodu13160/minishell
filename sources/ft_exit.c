/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:13:36 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/24 17:30:39 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

int	check_arg_exit(t_token *token, t_minishell *minishell, int i)
{
	if (!token[i].value)
	{
		minishell->code_error = 0;
		free_error(token, minishell, 1);
	}
	if (token[i].value && token[i + 1].value)
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
	while (token[i].value[x])
	{
		if (token[i].value[x] == '-')
			(*sign)++;
		else if (token[i].value[x] < '0' || token[i].value[x] > '9')
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

void	ft_exit(t_token *token, t_minishell *minishell, int i)
{
	int			error;
	int			sign;
	long long	value;

	error = 0;
	if (check_arg_exit(token, minishell, i) == 1)
		return ;
	if (check_exit_numeric(token, i, &sign) == 2)
	{
		minishell->code_error = 2;
		free_error(token, minishell, 1);
	}
	value = ft_atoll(token[i].value, &error);
	if (error)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		minishell->code_error = 2;
		free_error(token, minishell, 2);
	}
	if (sign)
		value = 256 - value;
	else if (value > 255)
		value = value % 256;
	minishell->code_error = value;
	free_error(token, minishell, 1);
}
