/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:34:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:52:40 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdlib.h>

int	check_path(char *str)
{
	long int	i;

	i = 0;
	while (str[i] && i <= 4095)
	{
		i++;
	}
	if (i >= 4095)
	{
		ft_printf_fd(2, "invalid directory , buffer size max 4096 error\n");
		return (1);
	}
	return (0);
}

int	copy_new_env(t_minishell *minishell, char *new_var)
{
	char	**new_env;
	int		i;

	i = 0;
	while (minishell->env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
	{
		return (1);
	}
	i = 0;
	while (minishell->env[i])
	{
		new_env[i] = minishell->env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(minishell->env);
	minishell->env = new_env;
	return (0);
}

int	check_var_exist(t_minishell *minishell, const char *name, int name_len)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], name, name_len) == 0
			&& minishell->env[i][name_len] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	replace_existing_var(t_minishell *minishell, char *new_var, int var_index)
{
	free(minishell->env[var_index - 1]);
	minishell->env[var_index - 1] = new_var;
	return (0);
}

void	declare_putenv(t_cd *cd, const char *name)
{
	cd->new_env = NULL;
	cd->name_len = 0;
	cd->error = 0;
	cd->var_index = 0;
	while (name[cd->name_len] && name[cd->name_len] != '=')
		cd->name_len++;
}
