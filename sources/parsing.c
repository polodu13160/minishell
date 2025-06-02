/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/01 15:42:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "parsing.h"
#include "token.h"

static int	process_dollar(t_token *token, t_minishell *minishell, int type)
{
	int		i;
	char	*temp;

	i = 1;
	temp = malloc(sizeof(char) * ft_strlen(token->value));
	if (!temp)
		return (1);
	while (token->value[i])
	{
		temp[i - 1] = token->value[i];
		i++;
	}
	temp[i - 1] = '\0';
	free(token->value);
	token->value = temp;
	token->value = check_quote_command(token->value);
	temp = return_env(token->value, minishell);
	free(token->value);
	token->value = temp;
	if (type || token->type == T_FORBID)
	{
		ft_putstr_fd("forbidden preprocessor, || or && or ; or () or \\ \n", 2);
		return (1);
	}
	return (0);
}

static int	process_env_tokens(t_token *token, t_minishell *minishell,
		int *type)
{
	char	*temp;

	temp = NULL;
	*type = T_WORD;
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
	else
	{
		temp = return_env(token->value, minishell);
		free(token->value);
		token->value = temp;
	}
	return (0);
}

static int	process_quotes_tokens(t_token *token, t_minishell *minishell)
{
	if (token->value[0] == '"' || token->value[0] == '\''
		|| ft_strchr(token->value, '$'))
		token->value = parse_quotes(token->value, minishell);
	else if (token->type == T_FUNC)
		token->value = check_quote_command(token->value);
	return (0);
}

static int	process_word_tokens(t_token *token, t_minishell *minishell)
{
	char	*temp;

	if (token->value[1] == '$' && token->value[0] == '"')
	{
		token->value = check_quote_command(token->value);
		token->type = T_ENV;
		temp = return_env(token->value, minishell);
		free(token->value);
		token->value = temp;
	}
	else if (token->value[0] == '"')
		token->value = check_quote_command(token->value);
	else if (token->value[0] == '\'')
		token->value = parse_single_quotes(token->value);
	return (0);
}

int	check_parsing(t_token *token, t_minishell *minishell)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (token[i].value)
	{
		if (token[i].value[0] == '"' || token[i].value[0] == '\''
			|| token[i].type == T_FUNC)
			ret = process_quotes_tokens(&token[i], minishell);
		else if (token[i].type == T_ENV)
		{
			ret = process_env_tokens(&token[i], minishell, &token[i].type);
			if (ft_strncmp(token[i].value, " ", 2) == 0)
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
