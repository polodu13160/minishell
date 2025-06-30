/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:53:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/29 20:41:27 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*ft_join_malloc(char *malloc_str1, char *malloc_str2)
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

char	*ft_chardup(char c)
{
	char	*malloc_char;

	malloc_char = ft_calloc(2, sizeof(char));
	if (malloc_char == NULL)
		return (NULL);
	*malloc_char = c;
	return (malloc_char);
}

char	*get_env_value(char *var_name, char **env)
{
	int		i;
	char	*env_value;
	size_t	name_len;

	if (!var_name)
		return (NULL);
	if (!env)
		return (ft_strdup("\0"));
	name_len = ft_strlen(var_name);
	if (name_len == 0)
		return (ft_strdup("$"));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0
			&& env[i][name_len] == '=')
		{
			env_value = ft_strdup(env[i] + name_len + 1);
			if (!env_value)
				return (NULL);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
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
