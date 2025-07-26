/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/26 19:36:34 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "stdio.h"

static int	handle_invalid_identifier(char *var_name)
{
	printf("export: '%s': not a valid identifier\n", var_name);
	return (1);
}

static int	handle_existing_variable(char *str, t_minishell *minishell)
{
	int	result;

	result = check_double(str, minishell);
	if (result)
		return (result);
	return (0);
}

static int	add_new_variable(char **str, t_minishell *minishell, int i)
{
	char	**temp_env;

	if (ft_strchr(str[i], '=') == NULL)
		return (0);
	temp_env = copy_env(minishell, str, i);
	if (!temp_env)
		return (1);
	minishell->env = temp_env;
	return (0);
}

static int	process_export_argument(char **str, t_minishell *minishell, int i)
{
	int	result;

	if (!is_valid_identifier(str[i]))
		return (handle_invalid_identifier(str[i]));
	result = handle_existing_variable(str[i], minishell);
	if (result == 2)
		return (result);
	return (add_new_variable(str, minishell, i));
}

int	ft_export(char **str, t_minishell *minishell)
{
	int	current_result;
	int	i;

	i = 1;
	if (!str[i])
		return (print_export(minishell));
	while (str[i])
	{
		current_result = process_export_argument(str, minishell, i);
		if (current_result == 1)
			return (1);
		else if (current_result > 1)
			return (10);
		i++;
	}
	return (0);
}
