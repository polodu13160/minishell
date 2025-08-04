/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_full_quote_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:04:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 19:04:17 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
# include <stdlib.h>

size_t	calculate_needed_size(char *str, t_minishell *minishell, int i,
		size_t total_size)
{
	char	*var_name;
	char	*value;
	int		var_len;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			var_name = extract_var_name(str, &i, &var_len);
			if (var_name)
			{
				value = get_env_value(var_name, minishell);
				if (value)
				{
					total_size += ft_strlen(value);
					free(value);
				}
				free(var_name);
			}
			i += var_len;
		}
		else
			i++;
	}
	return (total_size);
}

static char	*init_quote_parsing(char *str, t_index *index,
		t_minishell *minishell)
{
	char	*result;
	size_t	needed_size;

	index->i = 0;
	index->j = 0;
	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	result = ft_calloc(needed_size + ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	return (result);
}

static char	*remove_leading_dollar(char *str)
{
	char	*new_str;
	int		i;

	if (!str || str[0] != '$' || !str[1] || (str[1] != '\'' && str[1] != '"'))
		return (str);
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i + 1])
	{
		new_str[i] = str[i + 1];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*remove_outer_quotes(char *str, t_minishell *minishell)
{
	t_index	index;
	char	*result;

	str = remove_leading_dollar(str);
	if (!str)
		return (NULL);
	result = init_quote_parsing(str, &index, minishell);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (parse_quote_loop(str, minishell, &index, result))
		return (NULL);
	result[index.j] = '\0';
	free(str);
	return (result);
}
