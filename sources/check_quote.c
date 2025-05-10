/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:53:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/10 16:28:48 by antbonin         ###   ########.fr       */
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
	if (str[0] == '$')
		str = ft_strtrim(str, "$");
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
	int		i;
	char	*env_value;
	size_t	name_len;

	if (!var_name || !env)
		return (ft_strdup(""));
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

char	*return_env(char *str, t_minishell minishell)
{
	char	*var_name;

	var_name = str + 1;
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (ft_itoa(minishell.code_error));
	return (get_env_value(var_name, minishell.env));
}
