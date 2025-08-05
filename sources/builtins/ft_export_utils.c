/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:51:51 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/05 02:07:43 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
# include <stdlib.h>
#include "libft.h"

int	exist_return(char *str, int exists, t_minishell *minishell)
{
	char	*temp;
	int		i;

	if (ft_strchr(str, '=') == NULL)
		return (1);
	temp = ft_strdup(str);
	if (!temp)
		return (2);
	free(minishell->env[exists]);
	minishell->env[exists] = temp;
	i = 0;
	return (1);
}

int	same_var_name(char *env_var, char *new_var)
{
	int	i;

	i = 0;
	while (env_var[i] && new_var[i] && env_var[i] != '=' && new_var[i] != '=')
	{
		if (env_var[i] != new_var[i])
			return (0);
		i++;
	}
	return ((env_var[i] == '=' || env_var[i] == '\0') && (new_var[i] == '='
			|| new_var[i] == '\0'));
}

int	check_double(char *str, t_minishell *minishell, int j, int name_len)
{
	int	exists;

	exists = -1;
	if (str == NULL)
		return (2);
	while (str[name_len] && str[name_len] != '=')
		name_len++;
	while (minishell->env[j])
		j++;
	j--;
	while (j >= 0)
	{
		if (same_var_name(minishell->env[j], str))
		{
			exists = j;
			break ;
		}
		j--;
	}
	if (exists >= 0)
		return (exist_return(str, exists, minishell));
	return (0);
}

int	copy_env_loop(char **new_env, char **str, t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		new_env[j] = ft_strdup(minishell->env[j]);
		if (!new_env[j])
		{
			while (--j >= 0)
				free(new_env[j]);
			free(new_env);
			return (1);
		}
		j++;
	}
	new_env[j] = ft_strdup(str[i]);
	if (!new_env[j])
	{
		while (--j >= 0)
			free(new_env[j]);
		free(new_env);
		return (1);
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
