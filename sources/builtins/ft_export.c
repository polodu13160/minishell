/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/27 19:01:52 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "stdio.h"

static int	handle_existing_variable(char *str, t_minishell *minishell)
{
	int	result;

	result = check_double(str, minishell, 0, 0);
	if (result)
		return (result);
	return (0);
}

char	**copy_env(t_minishell *minishell, char **str, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (minishell->env[j])
		j++;
	new_env = ft_calloc(sizeof(char *), (j + 2));
	if (!new_env)
		return (NULL);
	if (copy_env_loop(new_env, str, minishell, i) == 1)
		return (NULL);
	j = 0;
	while (minishell->env[j])
		free(minishell->env[j++]);
	free(minishell->env);
	return (new_env);
}

static int	add_new_variable(char **str, t_minishell *minishell, int i)
{
	char	**temp_env;

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
	if (result == 1)
		return (0);
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
