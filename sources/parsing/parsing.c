/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/27 18:23:25 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "token.h"

static int	handle_env_quotes(t_token *token, t_minishell *minishell)
{
	char	*temp;

	if (token->value[1] == '"')
	{
		if (ft_strchr(token->value + 2, '$'))
		{
			temp = ft_strdup(token->value + 1);
			if (!temp)
				return (1);
			free(token->value);
			token->value = parse_quotes(temp, minishell);
		}
		else
			token->value = handle_double_quotes_env(token->value);
	}
	else if (token->value[1] == '\'')
		token->value = handle_single_quotes_env(token->value, 1, 0);
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\''))
		token->value = parse_quotes(token->value, minishell);
	if (!token->value)
		return (1);
	return (0);
}

static int	process_env_tokens(t_token *token, t_minishell *minishell)
{
	char	*temp;

	if (token->value[1] == '"' || token->value[1] == '\''
		|| ft_strchr(token->value, '"') || ft_strchr(token->value, '\''))
	{
		if (handle_env_quotes(token, minishell))
			return (1);
	}
	else
	{
		temp = return_env(token->value, minishell);
		if (!temp)
			return (1);
		free(token->value);
		token->value = temp;
	}
	if (!token->value)
		return (1);
	return (0);
}

static int	process_quotes_tokens(t_token *token, t_minishell *minishell)
{
	int	was_double_quoted;

	was_double_quoted = (token->value[0] == '"');
	if (ft_strchr(token->value, '$') && !ft_strchr(token->value, '\''))
	{
		token->value = parse_quotes(token->value, minishell);
		if (!token->value)
			return (1);
		if (!was_double_quoted)
			token->type = T_ENV;
	}
	else if (token->value[0] == '"' || token->value[0] == '\''
		|| ft_strchr(token->value, '$'))
	{
		token->value = parse_quotes(token->value, minishell);
		if (!token->value)
			return (1);
	}
	else if (token->type == T_FUNC)
		token->value = check_quote_command(token->value);
	if (!token->value)
	{
		return (1);
	}
	return (0);
}

static int	process_word_tokens(t_token *token, t_minishell *minishell,
		int is_in_double)
{
	if (ft_strchr(token->value, '$'))
	{
		if (ft_strchr(token->value, '"') && ft_strchr(token->value,
				'"') < ft_strchr(token->value, '$'))
		{
			is_in_double = 1;
			token->value = check_quote_command(token->value);
		}
		token->value = parse_env(token->value, minishell, is_in_double);
		if (ft_strchr(token->value, '"') || (ft_strchr(token->value, '\'')
				&& is_in_double != 1))
		{
			if (handle_env_quotes(token, minishell))
				return (1);
		}
		token->type = T_ENV;
	}
	else if (ft_strchr(token->value, '"'))
		token->value = check_quote_command(token->value);
	else if (ft_strchr(token->value, '\''))
		token->value = parse_single_quotes(token->value);
	if (!token->value)
		return (1);
	return (0);
}

int	check_parsing(t_token *t, t_minishell *minishell, int r, int i)
{
	while (t[i].type != T_NULL)
	{
		if (t[i].value == NULL)
		{
			i++;
			continue ;
		}
		if (t[i].value[0] == '"' || t[i].value[0] == '\''
			|| (t[i].type == T_FUNC))
			r = process_quotes_tokens(&t[i], minishell);
		else if (t[i].type == T_ENV)
		{
			r = process_env_tokens(&t[i], minishell);
			if (r == 0 && t[i].value && ft_strncmp(t[i].value, " ", 2) == 0)
				shift_token(t, i);
		}
		else if (t[i].type == T_WORD)
			r = process_word_tokens(&t[i], minishell, 0);
		if (r)
			return (r);
		i++;
	}
	return (0);
}
