/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/27 19:27:31 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "token.h"

static int	handle_env_quotes(t_token *token, t_minishell *minishell)
{
	if (token->value[1] == '"')
	{
		if (token->value[2] == '$')
		{
			if (process_dollar(token, minishell, 0, 0))
				return (1);
		}
		else
			token->value = handle_double_quotes_env(token->value);
	}
	else if (token->value[1] == '\'')
		token->value = handle_single_quotes_env(token->value);
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\''))
		token->value = parse_quotes(token->value, minishell);
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
		free(token->value);
		token->value = temp;
	}
	if (!token->value)
		return (1);
	return (0);
}

static int	process_quotes_tokens(t_token *token, t_minishell *minishell)
{
	if (ft_strchr(token->value, '$') && !ft_strchr(token->value, '\''))
	{
		token->value = parse_quotes(token->value, minishell);
		token->type = T_ENV;
	}
	else if (token->value[0] == '"' || token->value[0] == '\''
		|| ft_strchr(token->value, '$'))
		token->value = parse_quotes(token->value, minishell);
	else if (token->type == T_FUNC)
		token->value = check_quote_command(token->value);
	if (!token->value)
	{
		return (1);
	}
	return (0);
}

static int	process_word_tokens(t_token *token, t_minishell *minishell)
{
	if (ft_strchr(token->value, '$'))
	{
		token->value = parse_env(token->value, minishell);
		token->type = T_ENV;
	}
	else if (ft_strchr(token->value, '"'))
		token->value = check_quote_command(token->value);
	else if (ft_strchr(token->value, '\''))
		token->value = parse_single_quotes(token->value);
	if (!token->value)
	{
		return (1);
	}
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
		else if (t[i].type == T_FORBID)
			r = process_dollar(t, minishell, 1, 0);
		else if (t[i].type == T_WORD)
			r = process_word_tokens(&t[i], minishell);
		if (r)
			return (r);
		i++;
	}
	return (0);
}
