/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:30:39 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 20:27:48 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
# include <stdlib.h>

int	return_command(char **str, t_minishell *minishell, char **var_name)
{
	char	*temp;

	if (ft_strncmp(*str, "$?", 2) == 0)
	{
		(*str)++;
		(*str)++;
		temp = ft_itoa(minishell->return_command);
		if (!temp)
			return (1);
		if (*var_name == NULL)
			*var_name = temp;
		else
		{
			*var_name = join_malloc(*var_name, temp);
			free(temp);
		}
		if (*var_name == NULL)
			return (1);
	}
	return (0);
}

int	expand(char **str, char **var_name, char **var_env, t_minishell *minishell)
{
	if (**str == '$')
	{
		if (*(*str + 1) == '$')
		{
			(*str)++;
			(*str)++;
			*var_name = join_malloc(*var_name, ft_strdup("$$"));
		}
		else
		{
			*var_env = extract_var_env(*str);
			if (*var_env == NULL)
			{
				if (*var_name)
					free(*var_name);
				return (1);
			}
			*var_name = join_malloc(*var_name, get_env_value(*var_env + 1,
						minishell));
			(*str)++;
			while ((ft_isalnum(**str) == 1 && **str != '\0') || **str == '_')
				(*str)++;
		}
	}
	return (0);
}

char	*expand_environment_vars(char *str, t_minishell *minishell)
{
	static char	*var_name = NULL;
	char		*var_env;
	char		*return_value;

	var_env = NULL;
	if (*str == '\0')
	{
		return_value = var_name;
		var_name = NULL;
		return (return_value);
	}
	if (return_command(&str, minishell, &var_name))
		return (NULL);
	if (var_name == NULL)
		var_name = ft_strdup("");
	while (*str != '\0' && *str != '$')
		var_name = join_malloc(var_name, chardup(*str++));
	if (expand(&str, &var_name, &var_env, minishell))
		return (NULL);
	free(var_env);
	if (var_name == NULL)
		return (NULL);
	return (expand_environment_vars(str, minishell));
}

char	*copy_return_command(t_minishell *minishell, char *var_name)
{
	char	*temp;

	temp = ft_itoa(minishell->return_command);
	if (!temp)
		return (NULL);
	var_name = ft_strjoin(temp, var_name + 1);
	free(temp);
	if (!var_name)
	{
		free(var_name);
		return (NULL);
	}
	return (var_name);
}
