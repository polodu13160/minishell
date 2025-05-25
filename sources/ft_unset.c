/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:07 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/25 16:40:02 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"

static int	should_remove_var(char *env_var, char *var_to_remove)
{
	int	var_len;

	if (!env_var || !var_to_remove)
		return (0);
	var_len = ft_strlen(var_to_remove);
	if (var_len == 0)
		return (0);
	if (ft_strncmp(env_var, var_to_remove, var_len) == 0)
	{
		if (env_var[var_len] == '=' || env_var[var_len] == '\0')
			return (1);
	}
	return (0);
}

static int	count_remaining_vars(t_minishell *minishell, char *var_to_remove)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (minishell->env[i])
	{
		if (!should_remove_var(minishell->env[i], var_to_remove))
			count++;
		i++;
	}
	return (count);
}

static char	**copy_env_without_var(t_minishell *minishell, char *var_to_remove)
{
	char	**new_env;
	int		new_count;
	int		i;
	int		j;

	new_count = count_remaining_vars(minishell, var_to_remove);
	new_env = malloc(sizeof(char *) * (new_count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (minishell->env[i])
	{
		if (!should_remove_var(minishell->env[i], var_to_remove))
		{
			new_env[j] = minishell->env[i];
			j++;
		}
		else
			free(minishell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(minishell->env);
	return (new_env);
}

int	ft_unset(t_token *token, t_minishell *minishell, int i)
{
	char	*var_to_remove;
	char	**new_env;

	if (!token[i + 1].value || token[i + 1].type == T_NULL || token[i
			+ 1].type == T_PIPE)
		return (0);
	while (token[i + 1].value != NULL && token[i + 1].type != T_NULL && token[i
			+ 1].type != T_PIPE)
	{
		var_to_remove = token[i + 1].value;
		if (ft_strchr(var_to_remove, '='))
		{
			printf("minishell: unset: '%s': not a valid identifier",
				var_to_remove);
			i++;
			continue ;
		}
		new_env = copy_env_without_var(minishell, var_to_remove);
		if (!new_env)
			return (1);
		minishell->env = new_env;
		i++;
	}
	return (0);
}
