/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_more2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:24:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 13:40:02 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_redirect_in(char *str, int *i, int *token_index, t_token *token)
{
	if (str[*i + 1] == '<')
	{
		token[*token_index].value = ft_strdup("<<");
		if (!token[*token_index].value)
			return (1);
		token[*token_index].type = T_HEREDOC;
		(*token_index)++;
		(*i) += 2;
	}
	else
	{
		token[*token_index].value = ft_strdup("<");
		if (!token[*token_index].value)
			return (1);
		token[*token_index].type = T_REDIRECT_IN;
		(*token_index)++;
		(*i)++;
	}
	return (0);
}

int	is_redirect_out(char *str, int *i, int *token_index, t_token *token)
{
	if (str[*i + 1] == '|')
	{
		token[*token_index].value = ft_strdup(">|");
		if (!token[*token_index].value)
			return (1);
		token[*token_index].type = T_IGNORE;
		(*token_index)++;
		(*i) += 2;
		return (0);
	}
	if (str[*i + 1] == '>')
	{
		token[*token_index].value = ft_strdup(">>");
		if (!token[*token_index].value)
			return (1);
		token[*token_index].type = T_APPEND;
		(*token_index)++;
		(*i) += 2;
	}
	else
	{
		token[*token_index].value = ft_strdup(">");
		if (!token[*token_index].value)
			return (1);
		token[*token_index].type = T_REDIRECT_OUT;
		(*token_index)++;
		(*i)++;
	}
	return (0);
}

int	is_word(char *str, int *i, int *token_index, t_token *token)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '|'
		&& str[*i] != '<' && str[*i] != '>')
		(*i)++;
	token[*token_index].value = ft_substr(str, start, *i - start);
	if (!token[*token_index].value)
	{
		free(token);
		return (1);
	}
	if (*token_index == 0 || token[*token_index - 1].type == T_PIPE
		|| token[*token_index - 1].type == T_WORD)
		token[*token_index].type = T_FUNC;
	else
		token[*token_index].type = T_WORD;
	(*token_index)++;
	return (0);
}

int	is_special_token(char *str, int *i, int *token_index, t_token *token)
{
	if (str[*i] == '|')
		return (is_pipe(str, i, token_index, token));
	else if (str[*i] == '<')
		return (is_redirect_in(str, i, token_index, token));
	else if (str[*i] == '>')
		return (is_redirect_out(str, i, token_index, token));
	else if (str[*i] == '$')
		return (is_dollar(str, i, token_index, token));
	return (is_word(str, i, token_index, token));
}
