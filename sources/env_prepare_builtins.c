/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prepare_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:15:08 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/25 16:21:04 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"

char	**declare_env(void)
{
	char	**copy_env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	copy_env = ft_calloc(sizeof(char *), 3);
	if (!copy_env)
		return (NULL);
	copy_env[0] = ft_strjoin("PWD=", pwd);
	copy_env[1] = ft_strdup("SHLVL=1");
	if (!copy_env[0] || !copy_env[1])
	{
		free(copy_env);
		free(pwd);
		return (NULL);
	}
	free(pwd);
	return (copy_env);
}

int	env_loop(char **copy_env, char **env, int *i)
{
	int		shlvl_value;
	char	*shlvl_str;

	if (ft_strncmp(env[*i], "SHLVL=", 6) == 0)
	{
		shlvl_value = ft_atoi(env[*i] + 6, 0) + 1;
		shlvl_str = ft_itoa(shlvl_value);
		copy_env[*i] = ft_strjoin("SHLVL=", shlvl_str);
		free(shlvl_str);
	}
	else
		copy_env[*i] = ft_strdup(env[*i]);
	if (!copy_env[*i])
	{
		while (i > 0)
			free(copy_env[--(*i)]);
		free(copy_env);
		return (1);
	}
	return (0);
}

char	**copy_original_env(char **env)
{
	int		i;
	char	**copy_env;

	i = 0;
	if (!env || !env[0])
		return (declare_env());
	while (env[i])
		i++;
	copy_env = ft_calloc(sizeof(char *), (i + 1));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (env_loop(copy_env, env, &i))
			return (NULL);
		i++;
	}
	return (copy_env);
}

int	ft_env(t_minishell *minishell, int pwd)
{
	int		i;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	if (pwd)
	{
		printf("%s\n", cwd);
		return (0);
	}
	free(cwd);
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			if (ft_strchr(minishell->env[i], '='))
				printf("%s\n", minishell->env[i++]);
		}
	}
	else
		return (1);
	return (0);
}
