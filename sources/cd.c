/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/17 19:22:25 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

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
	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", new_pwd, 1);
	if (minishell->cwd)
		free(minishell->cwd);
	minishell->cwd = ft_strdup(new_pwd);
	return (0);
}

int	ft_cd(t_token *token, int i, t_minishell *minishell)
{
	char	*path;
	char	old_pwd[4096];

	if (!getcwd(old_pwd, 4096))
	{
		perror("cd: error retrieving current directory");
		return (1);
	}
	path = get_cd_path(token, i);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (handle_cd_error(path));
	return (update_pwd_vars(old_pwd, minishell));
}
