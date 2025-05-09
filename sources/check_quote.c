/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:53:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/09 18:39:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_strlen_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
				j++;
			i++;
		}
	}
	return (i - j);
}

char	*check_quote_command(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char *) * (ft_strlen_quote(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}

char	*get_env_value(char *var_name, char **env)
{
	int		index;
	char	*env_value;
	size_t	name_len;

	if (!var_name || !env)
		return (ft_strdup(""));
	name_len = ft_strlen(var_name);
	if (name_len == 0)
		return (ft_strdup("$"));
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], var_name, name_len) == 0
			&& env[index][name_len] == '=')
		{
			env_value = ft_strdup(env[index] + name_len + 1);
			if (!env_value)
				return (NULL);
			return (env_value);
		}
		index++;
	}
	return (ft_strdup(""));
}

char	*return_env(t_token *token, int i, t_minishell minishell)
{
	char	*var_name;

	var_name = token[i].value + 1;
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (ft_itoa(minishell.code_error));
	return (get_env_value(var_name, minishell.env));
}

void	is_var(void)
{
	int start;
	int end;
	start = i + 1;
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	var_name = ft_substr(str, start, end - start);
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		value = ft_itoa(minishell.code_error);
	else
	{
		value = get_env_value(var_name, minishell.env);
		*type = T_ENV;
	}
	temp = result;
	result = ft_strjoin(result, value);
	free(temp);
	free(value);
	free(var_name);
	i = end;
}

char	*expand_env_vars(int *type, char *str, t_minishell minishell)
{
	int		i;
	char	*result;
	int		start;
	int		end;
	char	*var_name;
	char	*value;
	char	*temp;
	char	c[2];

	i = 0;
	c[1] = '\0';
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && str[i
			+ 1] != '"')
		{
			start = i + 1;
			end = start;
			while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
				end++;
			var_name = ft_substr(str, start, end - start);
			if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
				value = ft_itoa(minishell.code_error);
			else
			{
				value = get_env_value(var_name, minishell.env);
				*type = T_ENV;
			}
			temp = result;
			result = ft_strjoin(result, value);
			free(temp);
			free(value);
			free(var_name);
			i = end;
		}
		else
		{
			c[0] = str[i];
			temp = result;
			result = ft_strjoin(result, c);
			free(temp);
			i++;
		}
	}
	return (result);
}
