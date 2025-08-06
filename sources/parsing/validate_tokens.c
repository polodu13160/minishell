/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 19:04:51 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdlib.h"

static int	handle_env_quotes(t_token *token, t_minishell *minishell)
{
	char	*temp;
	char	*result;

	result = NULL;
	if (token->value[1] == '"')
	{
		if (ft_strchr(token->value + 2, '$'))
		{
			temp = ft_strdup(token->value + 1);
			if (!temp)
				return (1);
			free(token->value);
			token->value = remove_outer_quotes(temp, minishell);
		}
		else
			token->value = handle_double_quotes_env(token->value, 0, 0);
	}
	else if (token->value[1] == '\'' && (ft_strrchr(token->value,
		'$') < ft_strrchr(token->value, '\'')))
		token->value = handle_single_quotes_env(token->value, 1, 0, result);
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\''))
		token->value = remove_outer_quotes(token->value, minishell);
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
		temp = expand_environment_vars(token->value, minishell);
		if (!temp)
			return (1);
		free(token->value);
		token->value = temp;
	}
	if (!token->value)
		return (1);
	return (0);
}

int	check_is_retokenizable(char *str)
{
	int	i;
	int	has_quotes;
	int	has_dollar;
	int	in_dquote;
	int	in_squote;
	int	dollar_in_quotes;

	i = 0;
	has_quotes = 0;
	has_dollar = 0;
	in_dquote = 0;
	in_squote = 0;
	dollar_in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			has_quotes = 1;
		if (str[i] == '$')
			has_dollar = 1;
		i++;
	}
	if (!has_quotes || !has_dollar)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			if (in_dquote || in_squote)
				dollar_in_quotes = 1;
		}
		i++;
	}
	return (!dollar_in_quotes);
}

static int	process_quotes_tokens(t_token *token, t_minishell *minishell,
		t_token *tokens, int i)
{
	if (check_is_retokenizable(token->value))
		token->type = T_ENV;
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		token->value = check_quote_command(token->value);
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\'')
			|| ft_strchr(token->value, '$'))
	{
		token->value = expand_mixed_quotes(token->value, minishell);
		if (!token->value)
			return (1);
	}
	else if (token->type == T_FUNC)
		token->value = check_quote_command(token->value);
	if (!token->value)
		return (1);
	return (0);
}

static int	process_word_tokens(t_token *token, t_minishell *minishell,
		t_token *tokens, int i)
{
	char	*temp;

	if (check_is_ambigous_condition(token, tokens, i))
	{
		temp = expand_environment_vars(token->value, minishell);
		if (!temp)
			return (1);
		free(token->value);
		token->value = temp;
		if (ft_strncmp(token->value, "", 2) == 0 || is_ambigous(token->value))
			token->type = T_AMBIGOUS;
	}
	if (ft_strchr(token->value, '$') || ft_strchr(token->value, '"')
		|| ft_strchr(token->value, '\''))
	{
		token->value = expand_mixed_quotes(token->value, minishell);
		if (!token->value)
			return (1);
		if (ft_strchr(token->value, '>') || ft_strchr(token->value, '<')
			|| ft_strchr(token->value, '|'))
			token->type = T_WORD;
		else
			token->type = T_ENV;
	}
	return (0);
}

int	validate_token(t_token *t, t_minishell *minishell, int r, int i)
{
	while (t[i].type != T_NULL)
	{
		if (t[i].value == NULL)
		{
			i++;
			continue ;
		}
		if ((t[i].value[0] == '"' || t[i].value[0] == '\''
				|| (t[i].value[0] == '$' && (t[i].value[1]
				&& (t[i].value[1] == '"' || t[i].value[1] == '\''))))
				|| before_is_heredoc(t, i)
				|| !check_is_retokenizable(t[i].value))
			r = process_quotes_tokens(&t[i], minishell, t, i);
		else if (t[i].type == T_ENV)
		{
			r = process_env_tokens(&t[i], minishell);
			if (r == 0 && t[i].value && ft_strncmp(t[i].value, " ", 2) == 0)
				shift_token(t, i);
		}
		else if (t[i].type == T_WORD || (t[i].type == T_FUNC))
			r = process_word_tokens(&t[i], minishell, t, i);
		if (r)
			return (r);
		i++;
	}
	return (0);
}
