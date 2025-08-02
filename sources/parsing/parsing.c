/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/02 14:30:37 by antbonin         ###   ########.fr       */
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
	else if (token->value[1] == '\'' && (ft_strrchr(token->value, '$') < ft_strrchr(token->value, '\'')))
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

static char	*parse_mixed_quotes_v2(char *str, t_minishell *minishell)
{
	char	*result;
	int		i = 0, j = 0;
	int		in_dquote = 0, in_squote = 0;
	size_t	needed_size;

	if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
		i = 1;
	
	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	result = ft_calloc(needed_size + ft_strlen(str) * 2 + 100, sizeof(char));
	if (!result)
		return (NULL);

	while (str[i])
	{
		if (str[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++; 
		}
		else if (str[i] == '$' && !in_squote)
		{
			 
			i++;
			if (str[i] == '?' || str[i] == '$')
			{
				char special[2] = {str[i], '\0'};
				char *value = get_env_value(special, minishell);
				if (value)
				{
					int k = 0;
					while (value[k])
						result[j++] = value[k++];
					free(value);
				}
				i++;
			}
			else if (ft_isalnum(str[i]) || str[i] == '_')
			{
				int var_start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				char *var_name = ft_substr(str, var_start, i - var_start);
				char *value = get_env_value(var_name, minishell);
				if (value)
				{
					int k = 0;
					while (value[k])
						result[j++] = value[k++];
					free(value);
				}
				free(var_name);
			}
			else
			{
				result[j++] = '$';
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	free(str);
	return (result);
}

static int	process_quotes_tokens(t_token *token, t_minishell *minishell,
		t_token *tokens, int i)
{
	int	do_not_expand;
	int	is_heredoc_delimiter;

	do_not_expand = 0;
	is_heredoc_delimiter = 0;
	
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		is_heredoc_delimiter = 1;
	
	if (is_heredoc_delimiter)
	{
		if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\'') || ft_strchr(token->value, '$'))
		{
			token->value = parse_mixed_quotes_v2(token->value, minishell);
			if (!token->value)
				return (1);
		}
		else
			token->value = check_quote_command(token->value);
	}
	else if (ft_strchr(token->value, '"') || ft_strchr(token->value, '\'') || ft_strchr(token->value, '$'))
	{
		token->value = parse_mixed_quotes_v2(token->value, minishell);
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
		int is_in_double)
{
	if (ft_strchr(token->value, '$') || ft_strchr(token->value, '"') || ft_strchr(token->value, '\''))
	{
		token->value = parse_mixed_quotes_v2(token->value, minishell);
		if (!token->value)
			return (1);
		token->type = T_ENV;
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
		if (t[i].value[0] == '"' || t[i].value[0] == '\'')
			r = process_quotes_tokens(&t[i], minishell, t, i);
		else if (t[i].type == T_ENV)
		{
			r = process_env_tokens(&t[i], minishell);
			if (r == 0 && t[i].value && ft_strncmp(t[i].value, " ", 2) == 0)
				shift_token(t, i);
		}
		else if (t[i].type == T_WORD || (t[i].type == T_FUNC))
			r = process_word_tokens(&t[i], minishell, 0);
		if (r)
			return (r);
		i++;
	}
	return (0);
}
