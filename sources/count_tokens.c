/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:59:30 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/11 16:08:58 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&' || c == '('
		|| c == ')' || c == '$')
		return (1);
	return (0);
}

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static void	process_count(char *str, int *j, int *count)
{
	(*count)++;
	if ((str[*j] == '>' && str[*j + 1] == '>') || (str[*j] == '<' && str[*j
				+ 1] == '<') || (str[*j] == '&' && str[*j + 1] == '&')
		|| (str[*j] == '|' && str[*j + 1] == '|'))
		(*j) += 2;
	else if (str[*j] == '$')
	{
		(*j)++;
		while (str[*j] && !is_whitespace(str[*j]) && !is_special_char(str[*j]))
			(*j)++;
	}
	else
		(*j)++;
}

static void	process_token(char *str, int *j, int *count)
{
	int	in_dquote;
	int	in_squote;

	in_dquote = 0;
	in_squote = 0;
	if (is_special_char(str[*j]))
	{
		if ((str[*j] == '|' && str[*j + 1] == '|') || (str[*j] == '&' && str[*j
					+ 1] == '&') || str[*j] == '(' || str[*j] == ')'
			|| str[*j] == '$' || (!in_dquote && !in_squote))
		{
			process_count(str, j, count);
			return ;
		}
	}
	(*count)++;
	while (str[*j] && ((in_dquote || in_squote) || (!is_whitespace(str[*j])
				&& !is_special_char(str[*j]))))
	{
		if (str[*j] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[*j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		(*j)++;
	}
}

int	count_tokens(char *str)
{
	int	i;
	int	token_count;

	i = 0;
	token_count = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (token_count);
		if (is_whitespace(str[i]))
		{
			i++;
			continue ;
		}
		process_token(str, &i, &token_count);
	}
	return (token_count);
}
