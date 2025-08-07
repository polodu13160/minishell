/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:53:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:38:20 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

char	*join_malloc(char *malloc_str1, char *malloc_str2)
{
	char	*join;

	if (!malloc_str1)
	{
		if (malloc_str2)
			free(malloc_str2);
		return (NULL);
	}
	if (!malloc_str2)
	{
		if (malloc_str1)
			free(malloc_str1);
		return (NULL);
	}
	join = ft_strjoin(malloc_str1, malloc_str2);
	free(malloc_str1);
	free(malloc_str2);
	if (join == NULL)
		return (NULL);
	return (join);
}

char	*chardup(char c)
{
	char	*malloc_char;

	malloc_char = ft_calloc(2, sizeof(char));
	if (malloc_char == NULL)
		return (NULL);
	*malloc_char = c;
	return (malloc_char);
}

char	*get_env_value_loop(char *var_name, t_minishell *minishell,
		int name_len, char *env_value)
{
	int	i;

	i = -1;
	if (var_name[0] == '?')
		return (copy_return_command(minishell, var_name));
	while (minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], var_name, name_len) == 0
			&& minishell->env[i][name_len] == '=')
		{
			env_value = ft_strdup(minishell->env[i] + name_len + 1);
			if (!env_value)
				return (NULL);
			return (env_value);
		}
	}
	return (ft_strdup(""));
}

char	*get_env_value(char *var_name, t_minishell *minishell)
{
	int		i;
	size_t	name_len;
	char	*env_value;

	env_value = NULL;
	if (!minishell->env)
		return (ft_strdup("\0"));
	name_len = ft_strlen(var_name);
	if (name_len == 0)
		return (ft_strdup("$"));
	i = -1;
	if (name_len == 1 && ft_strcmp("?", var_name) == 0)
		return (ft_itoa(minishell->return_command));
	return (get_env_value_loop(var_name, minishell, name_len, env_value));
}

char	*extract_var_env(char *str)
{
	char	*str_save;
	char	*null_str_save;

	while (*str != '$' && *str != '\0')
		str++;
	if (*str == '\0')
		return (NULL);
	str_save = ft_strdup(str);
	if (str_save == NULL)
		return (NULL);
	null_str_save = str_save + 1;
	while ((ft_isalnum(*null_str_save) == 1 && *null_str_save != '\0')
		|| *null_str_save == '_')
		null_str_save++;
	while (*null_str_save)
		*(null_str_save++) = '\0';
	return (str_save);
}
