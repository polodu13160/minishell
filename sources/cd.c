/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/18 20:25:21 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int	ft_putenv(const char *name, const char *value, int overwrite,
		t_minishell *minishell)
{
	char	*new_var;
	char	**new_env;
	int		name_len;
	int		error;

	new_env = NULL;
	error = 0;
	if (!name || !value || !minishell || !minishell->env)
		return (-1);
	name_len = 0;
	while (name[name_len] && name[name_len] != '=')
		name_len++;
	if (check_var_exist(minishell, name, name_len) && !overwrite)
		return (0);
	new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_var)
		return (-1);
	new_var = ft_strjoin3(name, "=", value);
	if (check_var_exist(minishell, name, name_len))
	{
		minishell->env[check_var_exist(minishell, name, name_len)] = new_var;
		return (0);
	}
	error += copy_new_env(minishell, new_env, new_var);
	return (error);
}

int	handle_cd_error(char *path)
{
	if (access(path, F_OK) == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("cd: permission denied: ", 2);
	else
		ft_putstr_fd("cd: not a directory: ", 2);
	ft_putendl_fd(path, 2);
	return (1);
}

int	update_pwd_vars(char *old_pwd, t_minishell *minishell)
{
	char	new_pwd[4096];

	if (!getcwd(new_pwd, 4096))
	{
		perror("cd: error retrieving current directory");
		return (1);
	}
	if (!ft_putenv("OLDPWD", old_pwd, 1, minishell))
		return (-1);
	if (!ft_putenv("PWD", new_pwd, 1, minishell))
		return (-1);
	if (minishell->cwd)
		free(minishell->cwd);
	minishell->cwd = ft_strdup(new_pwd);
	return (0);
}

char	*get_cd_path(t_token *token, int i)
{
	char	*path;

	if (!token[i + 1].value || !ft_strncmp(token[i + 1].value, "~", 1))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		path = token[i + 1].value;
	return (path);
}

int	ft_cd(t_token *token, int i, t_minishell *minishell)
{
	char	*path;
	char	old_pwd[4096];
	int		error;

	error = 0;
	if (!getcwd(old_pwd, 4096) || (token[i].value && token[i + 1].value
			&& token[i + 2].value && token[i + 2].type != T_PIPE))
	{
		perror("cd: error retrieving current directory");
		return (1);
	}
	path = get_cd_path(token, i);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		error += handle_cd_error(path);
		return (error);
	}
	error += update_pwd_vars(old_pwd, minishell);
	return (error);
}
