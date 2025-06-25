/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/25 16:23:54 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"

int	print_export(t_minishell *minishell)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		printf("declare -x %s\n", minishell->env[j]);
		j++;
	}
	return (0);
}

int	exist_return(char **str, int exists, int i, t_minishell *minishell)
{
	char	*temp;

	temp = ft_strdup(str[i + 1]);
	if (!temp)
		return (2);
	free(minishell->env[exists]);
	minishell->env[exists] = temp;
	return (1);
}

int	check_double(char **str, t_minishell *minishell, char *var_name, int i)
{
	int	j;
	int	exists;
	int	name_len;

	name_len = 0;
	j = 0;
	exists = -1;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	while (minishell->env[j])
	{
		if (ft_strncmp(minishell->env[j], var_name, name_len) == 0
			&& (minishell->env[j][name_len] == '='
			|| minishell->env[j][name_len] == '\0'))
		{
			exists = j;
			break ;
		}
		j++;
	}
	if (exists >= 0)
		return (exist_return(str, exists, i, minishell));
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
	j = 0;
	while (minishell->env[j])
	{
		new_env[j] = minishell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(str[i + 1]);
	if (!new_env[j])
	{
		free(new_env);
		return (NULL);
	}
	free(minishell->env);
	return (new_env);
}

int	ft_export(char **str, t_minishell *minishell, int i)
{
	char	*var_name;
	int		name_len;
	int		exists;
	char	**temp_env;

	if (!str[i + 1])
		return (print_export(minishell));
	while (str[i + 1] != NULL)
	{
		var_name = str[i + 1];
		name_len = 0;
		while (var_name[name_len] && var_name[name_len] != '=')
			name_len++;
		exists = -1;
		if (check_double(str, minishell, var_name, i))
			return (check_double(str, minishell, var_name, i) - 1);
		temp_env = copy_env(minishell, str, i);
		if (!temp_env)
			return (1);
		minishell->env = temp_env;
		i++;
	}
	return (0);
}
