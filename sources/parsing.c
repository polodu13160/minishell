/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/26 00:11:08 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "parsing.h"
#include "token.h"

static int	handle_env_quotes(t_token *token, t_minishell *minishell)
{
	if (token->value[1] == '"')
	{
		if (token->value[2] == '$')
		{
			if (process_dollar(token, minishell, 0))
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

static int	process_env_tokens(t_token *token, t_minishell *minishell,
		int *type)
{
	char	*temp;

	*type = T_WORD;
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
	if (token->value[0] == '"' || token->value[0] == '\''
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
		token->value = parse_env(token->value, minishell);
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

int	check_parsing(t_token *token, t_minishell *minishell, int ret, int i)
{
	while (token[i].type != T_NULL)
	{
		if (token[i].value == NULL)
		{
			i++;
			continue ;
		}
		if (token[i].value[0] == '"' || token[i].value[0] == '\''
			|| (token[i].type == T_FUNC && ft_strchr(token[i].value, '"')))
			ret = process_quotes_tokens(&token[i], minishell);
		else if (token[i].type == T_ENV)
		{
			ret = process_env_tokens(&token[i], minishell, &token[i].type);
			if (ret == 0 && ft_strncmp(token[i].value, " ", 2) == 0)
				shift_token(token, i);
		}
		else if (token[i].type == T_FORBID)
			ret = process_dollar(token, minishell, 1);
		else if (token[i].type == T_WORD)
			ret = process_word_tokens(&token[i], minishell);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}
