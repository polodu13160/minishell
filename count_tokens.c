/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:59:30 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/15 19:14:00 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static void	check_quote(char *str, int *j, int *count)
{
	if (str[*j] == '"')
	{
		(*count)++;
		(*j)++;
		while (str[*j] && str[*j] != '"')
			(*j)++;
		if (str[*j] == '"')
			(*j)++;
	}
	else if (str[*j] == '\'')
	{
		(*count)++;
		(*j)++;
		while (str[*j] && str[*j] != '\'')
			(*j)++;
		if (str[*j] == '\'')
			(*j)++;
	}
}

static void	process_token(char *str, int *j, int *count)
{
	if (str[*j] == '"' || str[*j] == '\'')
		check_quote(str, j, count);
	else if (is_special_char(str[*j]))
	{
		(*count)++;
		if ((str[*j] == '>' && str[*j + 1] == '>') || (str[*j] == '<' && str[*j
					+ 1] == '<'))
			(*j) += 2;
		else
			(*j)++;
	}
	else
	{
		(*count)++;
		while (str[*j] && !is_whitespace(str[*j]) && !is_special_char(str[*j])
			&& str[*j] != '"' && str[*j] != '\'')
			(*j)++;
	}
	return ;
}

int	count_tokens(char *str)
{
	int	i;
	int	token_count;

	i = 0;
	token_count = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
		{
			i++;
			continue ;
		}
		process_token(str, &i, &token_count);
	}
	printf("%d", token_count);
	return (token_count);
}
