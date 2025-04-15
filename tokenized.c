/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:34:13 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/15 19:42:18 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "token.h"

t_token	*tokenize(char *str)
{
	int		token_count;
	t_token	*tokens;
	int		i;
	int		token_index;
	int		start;

	token_count = count_tokens(str);
	tokens = malloc(sizeof(t_token) * (token_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	token_index = 0;
	while (str[i] && token_index < token_count)
	{
		while (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (!str[i])
			break ;
		if (str[i] == '"')
		{
			start = i;
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				i++;
			tokens[token_index].value = ft_substr(str, start, i - start);
			tokens[token_index].type = T_DOUBLE_QUOTE;
			token_index++;
		}
		else if (str[i] == '\'')
		{
			start = i;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
			tokens[token_index].value = ft_substr(str, start, i - start);
			tokens[token_index].type = T_SINGLE_QUOTE;
			token_index++;
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				tokens[token_index].value = ft_strdup("||");
				tokens[token_index].type = T_OR;
				token_index++;
				i += 2;
			}
			else
			{
				tokens[token_index].value = ft_strdup("|");
				tokens[token_index].type = T_PIPE;
				token_index++;
				i++;
			}
		}
		else if (str[i] == '&' && str[i + 1] == '&')
		{
			tokens[token_index].value = ft_strdup("&&");
			tokens[token_index].type = T_AND;
			token_index++;
			i += 2;
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				tokens[token_index].value = ft_strdup("<<");
				tokens[token_index].type = T_HEREDOC;
				token_index++;
				i += 2;
			}
			else
			{
				tokens[token_index].value = ft_strdup("<");
				tokens[token_index].type = T_REDIRECT_IN;
				token_index++;
				i++;
			}
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				tokens[token_index].value = ft_strdup(">>");
				tokens[token_index].type = T_APPEND;
				token_index++;
				i += 2;
			}
			else
			{
				tokens[token_index].value = ft_strdup(">");
				tokens[token_index].type = T_REDIRECT_OUT;
				token_index++;
				i++;
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|'
				&& str[i] != '<' && str[i] != '>')
				i++;
			tokens[token_index].value = ft_substr(str, start, i - start);
			tokens[token_index].type = T_WORD;
			token_index++;
		}
	}
	tokens[token_index].value = NULL;
	return (tokens);
}
