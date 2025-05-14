/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:34:13 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/13 21:13:11 by pde-petr         ###   ########.fr       */
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
				&& str[data->i] != '&' && str[data->i] != '('
				&& str[data->i] != ')' && str[data->i] != '\\')))
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
		if (str[data.i] == '#')
			return (0);
		if (str[data.i] == ' ' || str[data.i] == '\t')
			data.i++;
		data.start = data.i;
		if (!data.in_dquote && !data.in_squote && (str[data.i] == '|'
				|| str[data.i] == '<' || str[data.i] == '>'
				|| str[data.i] == ';' || str[data.i] == '&'
				|| str[data.i] == '$' || str[data.i] == '('
				|| str[data.i] == ')' || str[data.i] == '\\'))
		{
			if (is_special_token(str, &data.i, &data.token_index, token))
				return (1);
		}
		else if (process_token(str, token, &data))
			return (1);
	}
	return (0);
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

t_token	*tokenize(char *str, t_minishell *minishell)
{
	t_token	*tokens;
	int		count;
	int		i;

	i = 0;
	count = count_tokens(str);
	minishell->count_tokens = count;
	tokens = malloc(sizeof(t_token) * (count + 1));
	if (!tokens)
		return (NULL);
	// rajouter dans tokens ici
	while (i < count)
	{
		tokens[i].new_value = NULL;
		tokens[i++].option = NULL;
	}
	if (count_quote(str))
	{
		free(tokens);
		return (NULL);
	}
	if (check_args(str, tokens, minishell->count_tokens))
	{
		perror("Malloc error ");
		free_error(tokens, minishell);
	}
	tokens[count].value = NULL;
	return (tokens);
}
