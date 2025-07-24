/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prepare_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 15:50:46 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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
		if (copy_env[0])
			free(copy_env[0]);
		if (copy_env[1])
			free(copy_env[1]);
		free(copy_env);
		free(pwd);
		return (NULL);
	}
	free(pwd);
	return (copy_env);
}

int	env_loop(char **copy_env, char **env, int *i)
{
	if (ft_strncmp(env[*i], "SHLVL=", 6) == 0)
		copy_env[*i] = ft_strjoin("SHLVL=", "1");
	else if (ft_strchr(env[*i], '='))
		copy_env[*i] = ft_strdup(env[*i]);
	else
		return (0);
	if (!copy_env[*i])
	{
		while (*i > 0)
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
	int	i;

	i = 0;
	if (pwd)
	{
		printf("%s\n", minishell->cwd);
		return (0);
	}
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			if (ft_strchr(minishell->env[i], '='))
				printf("%s\n", minishell->env[i]);
			i++;
		}
	}
	else
		return (1);
	return (0);
}
