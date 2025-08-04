/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 16:16:29 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
# include <stdlib.h>

int	ft_strlen_quote(char *str)
{
	int	i;
	int	count;
	int	inside_squotes;
	int	inside_dquotes;

	i = 0;
	count = 0;
	inside_squotes = 0;
	inside_dquotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !inside_dquotes && !inside_squotes)
			inside_squotes = 1;
		else if (str[i] == '\'' && inside_squotes && !inside_dquotes)
			inside_squotes = 0;
		else if (str[i] == '"' && !inside_squotes && !inside_dquotes)
			inside_dquotes = 1;
		else if (str[i] == '"' && inside_dquotes && !inside_squotes)
			inside_dquotes = 0;
		else
			count++;
		i++;
	}
	return (count);
}

char	*check_quote_command(char *str)
{
	char			*copy;
	t_quote_state	state;
	t_index			index;

	str = prepare_string_for_quote_check(str);
	copy = allocate_quote_copy(str);
	if (!copy)
		return (NULL);
	state.in_squote = 0;
	state.in_dquote = 0;
	index.i = 0;
	index.j = 0;
	while (str[index.i])
		process_quote_character(str, copy, &state, &index);
	copy[index.j] = '\0';
	free(str);
	return (copy);
}

char	*parse_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[0] == '\'')
		i = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

int	process_dollar(t_token *token, t_minishell *minishell, int i)
{
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strlen(token->value));
	if (!temp)
		return (1);
	while (token->value[++i])
		temp[i - 1] = token->value[i];
	temp[ft_strlen(token->value) - 1] = '\0';
	free(token->value);
	token->value = temp;
	temp = check_quote_command(token->value);
	if (!temp)
		return (1);
	token->value = temp;
	temp = return_env(token->value, minishell);
	if (!temp)
		return (1);
	free(token->value);
	token->value = temp;
	return (0);
}

char	*parse_env(char *str, t_minishell *minishell, int is_in_double)
{
	char	*result;
	size_t	needed_size;

	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	if (needed_size == 1)
	{
		result = ft_strdup("$");
		if (!result)
		{
			free(str);
			return (NULL);
		}
		free(str);
		return (result);
	}
	result = ft_calloc(sizeof(char), needed_size);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	result = parse_env_loop(str, minishell, result, is_in_double);
	return (result);
}
