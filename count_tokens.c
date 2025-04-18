/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:59:30 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/18 18:35:01 by antbonin         ###   ########.fr       */
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

static void	process_token(char *str, int *j, int *count)
{
	int	in_dquote;
	int	in_squote;

	in_dquote = 0;
	in_squote = 0;
	if (is_special_char(str[*j]) && !in_dquote && !in_squote)
	{
		(*count)++;
		if ((str[*j] == '>' && str[*j + 1] == '>') || (str[*j] == '<' && str[*j
				+ 1] == '<') || (str[*j] == '&' && str[*j + 1] == '&'))
			(*j) += 2;
		else
			(*j)++;
	}
	else
	{
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
	printf("token_count = %d\n", token_count);
	return (token_count);
}
