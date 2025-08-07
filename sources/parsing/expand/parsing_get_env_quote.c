/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:26:00 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:40:01 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

char	*handle_single_quotes_env(char *str, int i, int j, char *result)
{
	result = ft_calloc(sizeof(char), ft_strlen(str));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[0] == '$')
		i = 1;
	if (str[i] == '\'')
		i++;
	copy_single(str, result, &i, &j);
	if (str[i] == '\'' && str[i + 1] != '\0')
	{
		i++;
		while (str[i])
		{
			if (str[i] == '\'')
				i++;
			else
				result[j++] = str[i++];
		}
	}
	free(str);
	return (result);
}

char	*handle_double_quotes_env(char *str, int i, int j)
{
	char	*result;

	result = ft_calloc(sizeof(char), ft_strlen(str));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '"' || str[i] == '$')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			continue ;
		}
		result[j++] = str[i];
		if (!str[i + 1])
			break ;
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
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
			else
				result[(*j)++] = str[(*i)++];
		}
		else
			result[(*j)++] = str[(*i)++];
	}
}

char	*new_str(char *str, t_minishell *minishell)
{
	char	*temp;
	char	*itoa;
	char	*new_str;

	temp = str;
	itoa = ft_itoa(minishell->return_command);
	if (!itoa)
		return (NULL);
	new_str = ft_strjoin(itoa, temp + 2);
	if (!temp)
	{
		free(itoa);
		return (NULL);
	}
	free(temp);
	free(itoa);
	return (new_str);
}

char	*parse_env_loop(char *str, t_minishell *minishell, char *result,
		int is_in_double)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	if (str[0] == '$' && str[1] == '?')
	{
		str = new_str(str, minishell);
		if (!str)
			return (NULL);
	}
	while (str[index.i] && result != NULL)
	{
		if ((!ft_strchr(str, '\'') && str[index.i] == '$') || (ft_strchr(str,
					'"') && (ft_strchr(str, '"') < ft_strchr(str, '\'')
					&& str[index.i] == '$')) || (is_in_double
				&& str[index.i] == '$'))
			process_env_var(str, result, &index, minishell);
		else
			result[index.j++] = str[index.i++];
	}
	result[index.j] = '\0';
	free(str);
	return (result);
}
