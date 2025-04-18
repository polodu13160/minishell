/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:34:13 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/18 19:42:04 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "token.h"

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
		|| token[*token_index - 1].type == T_AND || token[*token_index
		- 1].type == T_SEMICOLON)
		token[*token_index].type = T_FUNC;
	else
		token[*token_index].type = T_WORD;
	(*token_index)++;
	return (0);
}

int	is_special_char(char *str, int *i, int *token_index, t_token *token)
{
	if (str[*i] == '|')
		return (is_pipe(str, i, token_index, token));
	else if (str[*i] == '<')
		return (is_redirect_in(str, i, token_index, token));
	else if (str[*i] == '>')
		return (is_redirect_out(str, i, token_index, token));
	else if (str[*i] == ';')
		return (is_semicolon(str, i, token_index, token));
	else if (str[*i] == '&' && str[*i + 1] == '&')
		return (is_and(str, i, token_index, token));
	return (is_word(str, i, token_index, token));
}

void	check_args(char *str, t_token *token, int count, int *error)
{
	int	i;
	int	token_index;
	int	in_dquote;
	int	in_squote;
	int	start;

	i = 0;
	token_index = 0;
	in_dquote = 0;
	in_squote = 0;
	while (str[i] && token_index < count)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		start = i;
		if (!in_dquote && !in_squote && (str[i] == '|' || str[i] == '<'
				|| str[i] == '>' || str[i] == ';' || str[i] == '&'))
		{
			*error += is_special_char(str, &i, &token_index, token);
		}
		else
		{
			while (str[i] && ((in_dquote || in_squote) || (str[i] != ' '
						&& str[i] != '\t' && str[i] != '|' && str[i] != '<'
						&& str[i] != '>' && str[i] != ';' && str[i] != '&')))
			{
				if (str[i] == '"' && !in_squote)
					in_dquote = !in_dquote;
				else if (str[i] == '\'' && !in_dquote)
					in_squote = !in_squote;
				i++;
			}
			if (in_dquote || in_squote)
			{
				*error = 1;
				return ;
			}
			token[token_index].value = ft_substr(str, start, i - start);
			if (!token[token_index].value)
			{
				*error = 1;
				return ;
			}
			if (token_index == 0 || token[token_index - 1].type == T_PIPE
				|| token[token_index - 1].type == T_AND || token[token_index
				- 1].type == T_SEMICOLON)
				token[token_index].type = T_FUNC;
			else
				token[token_index].type = T_WORD;
			token_index++;
		}
	}
}

int	count_quote(char *str)
{
	int	i;
	int	count_d;
	int	count_s;

	i = 0;
	count_d = 0;
	count_s = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count_d++;
		else if (str[i] == '\'')
			count_s++;
		i++;
	}
	if (count_d % 2 != 0 || count_s % 2 != 0)
		return (1);
	return (0);
}

t_token	*tokenize(char *str)
{
	t_token	*tokens;
	int		count;
	int		error;

	error = 0;
	count = count_tokens(str);
	tokens = malloc(sizeof(t_token) * (count + 1));
	if (!tokens)
		return (NULL);
	if (count_quote(str))
	{
		free(tokens);
		return (NULL);
	}
	check_args(str, tokens, count, &error);
	if (error > 0)
		return (NULL);
	tokens[count].value = NULL;
	return (tokens);
}
