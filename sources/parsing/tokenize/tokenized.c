/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:53:35 by antbonin          #+#    #+#             */
/*   Updated: 2025/09/10 15:18:04 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"
#include "token.h"
#include "use_free.h"

static int	process_token(char *str, t_token *token, t_parse_data *data)
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

static void	init_data(t_parse_data *data)
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
	int				error;

	error = 0;
	init_data(&data);
	while (str[data.i] && data.token_index < count)
	{
		while (str[data.i] == ' ' || str[data.i] == '\t')
			data.i++;
		data.start = data.i;
		if (!data.in_dquote && !data.in_squote && (str[data.i] == '|'
				|| str[data.i] == '<' || str[data.i] == '>'))
		{
			error = is_special_token(str, &data.i, &data.token_index, token);
			if (error)
				return (error);
		}
		else if (process_token(str, token, &data))
			return (1);
	}
	return (0);
}

void	init_data_token(t_token *token, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		token[i].value = NULL;
		token[i].fd = -1;
		i++;
	}
}

int	tokenize(char *str, t_minishell *minishell, int count)
{
	t_token	*tokens;

	count = count_tokens(str);
	if (count == 0)
		return (1);
	tokens = ft_calloc(sizeof(t_token), (count + 1));
	if (!tokens)
		return (1);
	init_data_token(tokens, count);
	if (count_quote(str))
	{
		free(tokens);
		return (1);
	}
	tokens[count].type = T_NULL;
	if (check_token_args(str, tokens, count, minishell))
		return (1);
	minishell->tokens = tokens;
	return (0);
}
