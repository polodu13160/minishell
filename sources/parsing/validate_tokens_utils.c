/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:28:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 16:11:30 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "token.h"

int	check_is_ambigous_condition(t_token *token, t_minishell *minishell,
		t_token *tokens, int i)
{
	if (ft_strchr(token->value, '$') && !ft_strchr(token->value, '"')
		&& !ft_strchr(token->value, '\'') && before_is_ambigous(tokens, i))
		return (1);
	return (0);
}

int	before_is_heredoc(t_token *tokens, int i)
{
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		return (1);
	return (0);
}

int	before_is_ambigous(t_token *tokens, int i)
{
	if (i >= 1 && tokens[i - 1].value && (tokens[i - 1].type == T_APPEND
			|| tokens[i - 1].type == T_REDIRECT_IN || tokens[i
			- 1].type == T_REDIRECT_OUT))
		return (1);
	return (0);
}

int	is_ambigous(char *str)
{
	int	i;
	int	is_word;

	i = -1;
	while (str[++i])
	{
		if (!is_whitespace(str[i]))
			break ;
	}
	if (i == (int)ft_strlen(str))
		return (1);
	i = -1;
	is_word = 0;
	while (str[++i])
	{
		if (!is_whitespace(str[i]))
			is_word = 1;
		if (is_whitespace(str[i]) && str[i + 1] && !is_whitespace(str[i + 1])
			&& is_word == 1)
			return (1);
	}
	return (0);
}

void	shift_token(t_token *token, int i)
{
	free(token[i].value);
	while (token[i + 1].type != T_NULL)
	{
		token[i] = token[i + 1];
		i++;
	}
	token[i].value = NULL;
	token[i].type = T_NULL;
}

void	get_token_index(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		tokens[i].index = i;
		i++;
	}
}
