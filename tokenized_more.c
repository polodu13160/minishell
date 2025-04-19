/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:51:02 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/19 15:34:39 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	double_quote(char *str, int *i, int *token_index, t_token *token)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '"')
		(*i)++;
	token[*token_index].value = ft_substr(str, start, *i - start);
	if (!token[*token_index].value)
		return (1);
	token[*token_index].type = T_WORD;
	if (*token_index == 0 || token[*token_index - 1].type == T_PIPE
		|| token[*token_index - 1].type == T_AND || token[*token_index
			- 1].type == T_SEMICOLON)
		token[*token_index].type = T_FUNC;
	(*token_index)++;
	return (0);
}

int	single_quote(char *str, int *i, int *token_index, t_token *token)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	token[*token_index].value = ft_substr(str, start, *i - start);
	if (!token[*token_index].value)
		return (1);
	token[*token_index].type = T_WORD;
	if (*token_index == 0 || token[*token_index - 1].type == T_PIPE
		|| token[*token_index - 1].type == T_AND || token[*token_index
			- 1].type == T_SEMICOLON)
		token[*token_index].type = T_FUNC;
	(*token_index)++;
	return (0);
}

int	is_pipe(char *str, int *i, int *token_index, t_token *token)
{
	(void)str;
	token[*token_index].value = ft_strdup("|");
	if (!token[*token_index].value)
		return (1);
	token[*token_index].type = T_PIPE;
	(*token_index)++;
	(*i)++;
	return (0);
}

int	is_dollar(char *str, int *i, int *token_index, t_token *token)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '|'
		&& str[*i] != '<' && str[*i] != '>')
		(*i)++;
	token[*token_index].value = ft_substr(str, start, *i - start);
	if (!token[*token_index].value)
		return (1);
	token[*token_index].type = T_ENV;
	(*token_index)++;
	return (0);
}

int	is_semicolon(char *str, int *i, int *token_index, t_token *token)
{
	(void)str;
	token[*token_index].value = ft_strdup(";");
	if (!token[*token_index].value)
		return (1);
	token[*token_index].type = T_SEMICOLON;
	(*token_index)++;
	(*i)++;
	return (0);
}
