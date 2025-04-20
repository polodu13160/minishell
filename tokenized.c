/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:34:13 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/20 17:09:17 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "token.h"

int	process_token(char *str, t_token *token, t_parse_data *data)
{
	while (str[data->i] && ((data->in_dquote || data->in_squote)
			|| (str[data->i] != ' ' && str[data->i] != '\t'
				&& str[data->i] != '|' && str[data->i] != '<'
				&& str[data->i] != '>' && str[data->i] != ';'
				&& str[data->i] != '&')))
	{
		if (str[data->i] == '"' && !data->in_squote)
			data->in_dquote = !data->in_dquote;
		else if (str[data->i] == '\'' && !data->in_dquote)
			data->in_squote = !data->in_squote;
		data->i++;
	}
	if (data->in_dquote || data->in_squote)
		return (1);
	token[data->token_index].value = ft_substr(str, data->start, data->i
			- data->start);
	if (!token[data->token_index].value)
		return (1);
	if (data->token_index == 0 || token[data->token_index - 1].type == T_PIPE
		|| token[data->token_index - 1].type == T_FORBID || token[data->token_index
			- 1].type == T_SEMICOLON)
		token[data->token_index++].type = T_FUNC;
	else
		token[data->token_index++].type = T_WORD;
	return (0);
}

void	init_data(t_parse_data *data, int *error)
{
	data->in_dquote = 0;
	data->in_squote = 0;
	data->error = error;
	data->token_index = 0;
	data->start = 0;
	data->i = 0;
}

void	check_args(char *str, t_token *token, int count, int *error)
{
	t_parse_data	data;

	init_data(&data, error);
	while (str[data.i] && data.token_index < count)
	{
		if (str[data.i] == ' ' || str[data.i] == '\t')
		{
			data.i++;
			continue ;
		}
		data.start = data.i;
		if (!data.in_dquote && !data.in_squote && (str[data.i] == '|'
				|| str[data.i] == '<' || str[data.i] == '>'
				|| str[data.i] == ';' || str[data.i] == '&'
			|| str[data.i] == '$' || str[data.i] == '(' || str[data.i] == ')'))
		{
			*error += is_special_token(str, &data.i, &data.token_index, token);
		}
		else
			*error += process_token(str, token, &data);
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
