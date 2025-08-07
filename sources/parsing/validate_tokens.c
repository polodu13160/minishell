/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 20:24:15 by antbonin         ###   ########.fr       */
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

static int	process_quotes_tokens(t_token *token, t_minishell *minishell,
		t_token *tokens, int i)
{
	char	*temp;
	char	*old_token;
	int		had_dollar;

	if (check_is_ambigous_condition(token, tokens, i))
	{
		old_token = ft_strdup(token->value);
		if (!old_token)
		return (1);
		temp = expand_environment_vars(token->value, minishell);
		if (!temp)
		{
			free(old_token);
			return (1);
		}
		free(token->value);
		token->value = temp;
		if (ft_strncmp(token->value, "", 2) == 0 || is_ambigous(token->value))
		{
			free(token->value);
			token->type = T_AMBIGOUS;
			token->value = old_token;
			return (0);
		}
		free(old_token);
	}
	if (check_is_retokenizable(token->value))
			token->type = T_ENV;
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		token->value = check_quote_command(token->value);
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\'')
			|| ft_strchr(token->value, '$'))
	{
		had_dollar = (ft_strchr(token->value, '$') != NULL);
		token->value = expand_mixed_quotes(token->value, minishell);
		if (!token->value)
			return (1);
		if (ft_strcmp(token->value, "") == 0 && had_dollar)
			token->type = T_ENV;
	}
	else if (token->type == T_FUNC)
		token->value = check_quote_command(token->value);
	// if (check_is_retokenizable(token->value))
	// 	token->type = T_ENV;
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
		if (should_process_ambigous_heredoc(t, i))
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
