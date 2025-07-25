/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:53:35 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 16:19:15 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "token.h"

int	process_token(char *str, t_token *token, t_parse_data *data)
{
	while (str[data->i] && ((data->in_dquote || data->in_squote)
			|| (str[data->i] != ' ' && str[data->i] != '\t'
				&& str[data->i] != '|' && str[data->i] != '<'
				&& str[data->i] != '>')))
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
	if (data->token_index == 0 || token[data->token_index - 1].type == T_PIPE)
		token[data->token_index++].type = T_FUNC;
	else
		token[data->token_index++].type = T_WORD;
	return (0);
}

void	init_data(t_parse_data *data)
{
	data->in_dquote = 0;
	data->in_squote = 0;
	data->token_index = 0;
	data->start = 0;
	data->i = 0;
}

int	check_args(char *str, t_token *token, int count)
{
	t_parse_data	data;

	init_data(&data);
	while (str[data.i] && data.token_index < count)
	{
		while (str[data.i] == ' ' || str[data.i] == '\t')
			data.i++;
		data.start = data.i;
		if (!data.in_dquote && !data.in_squote && (str[data.i] == '|'
				|| str[data.i] == '<' || str[data.i] == '>'))
		{
			if (is_special_token(str, &data.i, &data.token_index, token))
				return (1);
		}
		else if (process_token(str, token, &data))
			return (1);
	}
	return (0);
}

void	init_data_null(t_token *token, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		token[i].value = NULL;
		token[i++].option = NULL;
	}
}

int	tokenize(char *str, t_minishell *minishell)
{
	t_token	*tokens;
	int		count;

	count = count_tokens(str);
	if (count == 0)
		return (1);
	tokens = ft_calloc(sizeof(t_token), (count + 1));
	if (!tokens)
		return (1);
	init_data_null(tokens, count);
	if (count_quote(str))
	{
		free(tokens);
		return (1);
	}
	tokens[count].type = T_NULL;
	if (check_args(str, tokens, count))
	{
		free_token(tokens);
		perror("Error Malloc");
		minishell->tokens = NULL;
		return (1);
	}
	minishell->tokens = tokens;
	return (0);
}
