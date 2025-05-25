/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:07:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/25 15:44:29 by antbonin         ###   ########.fr       */
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

int	exist_return(t_token *token, int exists, int i, t_minishell *minishell)
{
	char	*temp;

	temp = ft_strdup(token[i + 1].value);
	if (!temp)
		return (2);
	free(minishell->env[exists]);
	minishell->env[exists] = temp;
	return (1);
}

int	check_double(t_token *token, t_minishell *minishell, char *var_name, int i)
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
		return (exist_return(token, exists, i, minishell));
	return (0);
}

char	**copy_env(t_minishell *minishell, t_token *token, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (minishell->env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while (minishell->env[j])
	{
		new_env[j] = minishell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(token[i + 1].value);
	if (!new_env[j])
	{
		while (i > 0)
			free(new_env[--j]);
		free(new_env);
	}
	new_env[j + 1] = NULL;
	free(minishell->env);
	return (new_env);
}

int	ft_export(t_token *token, t_minishell *minishell, int i)
{
	char	*var_name;
	int		name_len;
	int		exists;

	if (!token[i + 1].value)
		return (print_export(minishell));
	while (token[i + 1].type != T_PIPE && token[i + 1].type != T_NULL && token[i
			+ 1].value != NULL)
	{
		var_name = token[i + 1].value;
		name_len = 0;
		while (var_name[name_len] && var_name[name_len] != '=')
			name_len++;
		exists = -1;
		if (check_double(token, minishell, var_name, i))
			return (check_double(token, minishell, var_name, i) - 1);
		minishell->env = copy_env(minishell, token, i);
		i++;
	}
	return (0);
}
