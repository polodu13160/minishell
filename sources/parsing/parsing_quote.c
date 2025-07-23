/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/22 15:35:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token.h"

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
	while (str[i] && str[i] != '\'')
		result[j++] = str[i++];
	free(str);
	return (result);
}

int	process_dollar(t_token *token, t_minishell *minishell, int type, int i)
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
	if (type || token->type == T_FORBID)
	{
		ft_putstr_fd("forbidden preprocessor, || or && or ; or () or \\ \n", 2);
		return (1);
	}
	return (0);
}

char	*parse_env(char *str, t_minishell *minishell)
{
	t_index	index;
	char	*result;
	size_t	needed_size;

	index.i = 0;
	index.j = 0;
	// if (ft_strrchr(str, '\'') > ft_strrchr(str, '$'))
	// 	return (str);
	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	result = ft_calloc(sizeof(char), needed_size);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	while (str[index.i] && result != NULL)
	{
		if (str[index.i] == '$')
			process_env_var(str, result, &index, minishell);
		else
			result[index.j++] = str[index.i++];
	}
	result[index.j] = '\0';
	free(str);
	return (result);
}
