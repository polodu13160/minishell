/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:53:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/29 18:09:55 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char *ft_join_malloc(char *malloc_str1, char *malloc_str2)
{
	char *join;
	if (!malloc_str1)
	{

		if (malloc_str2)
			free(malloc_str2);
		return NULL;
	}
	if (!malloc_str2)
	{

		if (malloc_str1)
			free(malloc_str1);
		return NULL;
	}
	join = ft_strjoin(malloc_str1,malloc_str2);
	free(malloc_str1);
	free(malloc_str2);
	if (join == NULL)
		return NULL;
	return join;
}
char *ft_chardup(char c)
{
	char *malloc_char;
	malloc_char = ft_calloc(2,sizeof(char));
	if (malloc_char == NULL)
		return NULL;
	*malloc_char = c;
	return malloc_char;
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
//antoine ton extract var n peut pas etre adapter ailleur il faudrait..
char *extract_var_env(char *str)
{
	char *str_save;
	char *null_str_save;


	while (*str != '$' && *str != '\0')
		str++;
	if (*str == '\0')
		return NULL;
	str_save = ft_strdup(str);
	if (str_save == NULL)
		return NULL;
	null_str_save = str_save + 1;
	while ((ft_isalnum(*null_str_save) == 1 && *null_str_save != '\0') || *null_str_save == '_' )
		null_str_save++;
	while (*null_str_save)
		*(null_str_save++) = '\0';
	return str_save;
}
//est ce que cela protege au dessus ?si retourne null
char	*return_env(char *str, t_minishell *minishell)
{
	static char	*var_name = NULL;
	char *var_env;

	char *return_value;
	var_env = NULL;

	if (*str == '\0')
	{
		return_value = var_name;
		var_name = NULL;
		return return_value;
	}

	if (ft_strncmp(str, "$?", 2) == 0)
	{

		str++;
		str++;
		if (*(str+2) != '\0' && var_name == NULL)
			var_name = ft_itoa(minishell->return_command);
		else
			var_name = ft_join_malloc(var_name,ft_itoa(minishell->return_command));
		if (var_name == NULL)
			return NULL;
	}
	if (var_name == NULL)
          var_name = ft_strdup("");
	while (*str != '\0' && *str != '$')
	{
		var_name = ft_join_malloc(var_name, ft_chardup(*str));
		str++;
	}
	if (*str == '$')
	{
		if (*(str+1) == '$')
		{
			str++;
			str++;
			var_name = ft_join_malloc(var_name, ft_strdup("$$"));
		}
		else
		{
			var_env = extract_var_env(str);
			if (var_env == NULL)
			{
				if (var_name)
					free(var_name);
				return NULL;
			}
			var_name = ft_join_malloc(var_name, get_env_value(var_env+1, minishell->env));
			str++;
			while ((ft_isalnum(*str) == 1 && *str != '\0') || *str == '_')
					str++;
		}
	}
	free(var_env);
	if (var_name == NULL)
		return NULL;
	return return_env(str,minishell);
}

void	copy_single(char *str, char *result, int *i, int *j)
{
	while (str[(*i)] && str[(*i)] != '\'')
	{
		if (str[(*i)] == '\\')
		{
			if (str[(*i) + 1] == 't')
			{
				result[(*j)++] = '\t';
				(*i) += 2;
			}
			else if (str[(*i) + 1] == 'n')
			{
				result[(*j)++] = '\n';
				(*i) += 2;
			}
			else if (str[(*i) + 1] == '0')
			{
				result[(*j)++] = '\0';
				(*i) += 2;
			}
		}
		result[(*j)++] = str[(*i)++];
	}
}

char	*handle_single_quotes_env(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 1;
	j = 0;
	result = ft_calloc(sizeof(char), ft_strlen(str));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\'')
		i++;
	copy_single(str, result, &i, &j);
	if (str[i] == '\'' && str[i + 1] != '\0')
	{
		i++;
		while (str[i])
		{
			result[j++] = str[i++];
		}
	}
	free(str);
	return (result);
}

char	*handle_double_quotes_env(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 1;
	j = 0;
	result = ft_calloc(sizeof(char), ft_strlen(str));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '"')
		i++;
	while (str[i] && str[i] != '"')
		result[j++] = str[i++];
	if (str[i] == '"' && str[i + 1] != '\0')
	{
		i++;
		while (str[i])
			result[j++] = str[i++];
	}
	free(str);
	return (result);
}
