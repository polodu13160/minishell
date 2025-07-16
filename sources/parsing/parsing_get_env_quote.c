/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:26:00 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/30 16:48:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
