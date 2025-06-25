/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/25 16:15:53 by antbonin         ###   ########.fr       */
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
	t_cd	cd;

	if (!name || !value || !minishell || !minishell->env)
		return (-1);
	declare_putenv(&cd, name);
	if (check_var_exist(minishell, name, cd.name_len) && !overwrite)
		return (0);
	cd.new_var = ft_strjoin3(name, "=", value);
	if (!cd.new_var)
		return (-1);
	cd.var_index = check_var_exist(minishell, name, cd.name_len);
	if (cd.var_index)
		return (replace_existing_var(minishell, cd.new_var, cd.var_index));
	cd.error = copy_new_env(minishell, cd.new_var);
	if (cd.error)
		free(cd.new_var);
	return (cd.error);
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
	if (ft_putenv("OLDPWD", old_pwd, 1, minishell))
		return (1);
	if (ft_putenv("PWD", new_pwd, 1, minishell))
		return (1);
	if (minishell->cwd)
		free(minishell->cwd);
	minishell->cwd = ft_strdup(new_pwd);
	return (0);
}

char	*get_cd_path(char **str, int i)
{
	char	*path;

	if (!str[i + 1] || !ft_strncmp(str[i + 1], "~", 1))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		path = str[i + 1];
	return (path);
}

int	ft_cd(char **str, int i, t_minishell *minishell)
{
	char	*path;
	char	old_pwd[4096];
	int		error;

	error = 0;
	if (!getcwd(old_pwd, 4096) || (str[0] && str[1] && str[2]))
	{
		perror("cd: error retrieving current directory");
		return (1);
	}
	path = get_cd_path(str, i);
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
