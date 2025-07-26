/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:51:51 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/26 20:13:50 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_export(t_minishell *minishell)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		ft_printf("%s\n", minishell->env[j]);
		j++;
	}
	return (0);
}

int	exist_return(char *str, int exists, t_minishell *minishell)
{
	char	*temp;
	int		i;

	if (ft_strchr(str, '=') == NULL)
		return (1);
	temp = ft_strdup(str);
	if (!temp)
		return (2);
	free(minishell->env[exists]);
	minishell->env[exists] = temp;
	i = 0;
	return (1);
}

int	check_double(char *str, t_minishell *minishell)
{
	int	j;
	int	exists;
	int	name_len;

	name_len = 0;
	j = 0;
	exists = -1;
	if (str == NULL)
		return (2);
	while (str[name_len] && str[name_len] != '=')
		name_len++;
	if (str[name_len] != '=')
		return (0);
	while (minishell->env[j])
	{
		if (ft_strcmp_whithout_equality(minishell->env[j], str) == 0)
		{
			exists = j;
			break ;
		}
		j++;
	}
	if (exists >= 0)
		return (exist_return(str, exists, minishell));
	return (0);
}

char	**copy_env(t_minishell *minishell, char **str, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	while (minishell->env[j])
		j++;
	new_env = ft_calloc(sizeof(char *), (j + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while (minishell->env[j])
	{
		new_env[j] = minishell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(str[i]);
	if (!new_env[j])
	{
		free(new_env);
		return (NULL);
	}
	free(minishell->env);
	return (new_env);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
