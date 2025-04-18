/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_more2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:24:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/17 18:57:48 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

int	is_and(char *str, int *i, int *token_index, t_token *token)
{
	(void)str;
	token[*token_index].value = ft_strdup("&&");
	if (!token[*token_index].value)
			return (1);
	token[*token_index].type = T_AND;
	(*token_index)++;
	(*i) += 2;
	return (0);
}

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
