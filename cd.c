/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/05 17:54:56 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_libft/ressource/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <unistd.h>   // chdir

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	char	*existing;
	char	*env_var;
	int		i;
	int		j;

	existing = getenv(name);
	if (!overwrite && existing)
		return (0);
	env_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!env_var)
		return (-1);
	i = 0;
	j = 0;
	while (name[j])
		env_var[i++] = name[j++];
	env_var[i++] = '=';
	j = 0;
	while (value[j])
		env_var[i++] = value[j++];
	env_var[i] = '\0';
	if (putenv(env_var) != 0)
		return (free(env_var), -1);
	return (0);
}

int	cd(char **args)
{
	char	old_cwd[1024];
	char	new_cwd[1024];

	if (!args[1])
		return (1);
	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
		return (1);
	if (chdir(args[1]) != 0)
		return (1);
	if (getcwd(new_cwd, sizeof(new_cwd)) != NULL)
	{
		ft_setenv("OLDPWD", old_cwd, 1);
		ft_setenv("PWD", new_cwd, 1);
	}
	return (0);
}
