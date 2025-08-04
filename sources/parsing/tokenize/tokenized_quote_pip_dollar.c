/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_quote_pip_dollar.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:51:02 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 18:36:32 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
