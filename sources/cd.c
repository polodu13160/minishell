/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:01:15 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/16 16:23:12 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <unistd.h>  

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

int	ft_cd(t_token *token, int i)
{
	char	old_cwd[1024];
	char	new_cwd[1024];

	if (!token[i + 1].value)
		return (1);
	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
		return (1);
	if (chdir(token[i + 1].value) != 0)
		return (1);
	if (getcwd(new_cwd, sizeof(new_cwd)) != NULL)
	{
		ft_setenv("OLDPWD", old_cwd, 1);
		ft_setenv("PWD", new_cwd, 1);
	}
	return (0);
}
