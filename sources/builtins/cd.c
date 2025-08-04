/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 16:22:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/stat.h>
#include <unistd.h>
# include <stdlib.h>

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
	ft_printf_fd(2, "%s\n", path);
	return (1);
}

int	update_pwd_vars(char *old_pwd, t_minishell *minishell)
{
	char	new_pwd[4096];

	if (!getcwd(new_pwd, 4096))
	{
		ft_printf_fd(2, "cd: error retrieving current directory");
		return (1);
	}
	if (ft_putenv("OLDPWD", old_pwd, 1, minishell))
		return (1);
	if (ft_putenv("PWD", new_pwd, 1, minishell))
		return (1);
	if (minishell->cwd)
		free(minishell->cwd);
	minishell->cwd = ft_strdup(new_pwd);
	if (!minishell->cwd)
		return (1);
	return (0);
}

char	*get_cd_path(char **str, int i, t_minishell *minishell)
{
	char	*path;
	char	*home_value;

	if (!str[i + 1])
	{
		home_value = get_env_value("HOME", minishell);
		if (!home_value || ft_strlen(home_value) == 0)
		{
			if (home_value)
				free(home_value);
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home_value);
	}
	else
		path = str[i + 1];
	return (ft_strdup(path));
}

int	ft_cd(char **str, t_minishell *minishell, int error,
		int return_func_check_path)
{
	char	*path;
	char	*old_pwd;

	old_pwd = minishell->cwd;
	if (!old_pwd || (str[0] && str[1] && str[2]))
	{
		ft_printf_fd(2, "cd: error retrieving current directory\n");
		return (1);
	}
	path = get_cd_path(str, 0, minishell);
	if (!path)
		return (1);
	return_func_check_path = check_path(path);
	if (return_func_check_path || chdir(path) != 0)
	{
		if (!return_func_check_path)
			error = handle_cd_error(path);
		else
			error = 1;
		free(path);
		return (error);
	}
	error += update_pwd_vars(old_pwd, minishell);
	free(path);
	return (error);
}
