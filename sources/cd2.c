/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:34:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/24 16:15:34 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "stdlib.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

int	copy_new_env(t_minishell *minishell, char **new_env, char *new_var)
{
	int	i;

	i = 0;
	while (minishell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
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
	free(new_var);
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
			return (i);
		i++;
	}
	return (0);
}

int	replace_existing_var(t_minishell *minishell, char *new_var, int var_index)
{
	free(minishell->env[var_index]);
	minishell->env[var_index] = new_var;
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
