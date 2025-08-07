/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_retokenizable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:13:45 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:34:30 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_quotes_and_dollars(char *str)
{
	int	i;
	int	has_quotes;
	int	has_dollar;

	i = 0;
	has_quotes = 0;
	has_dollar = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			has_quotes = 1;
		if (str[i] == '$')
			has_dollar = 1;
		i++;
	}
	return (has_quotes && has_dollar);
}

static void	update_quote_state(char c, int *in_dquote, int *in_squote)
{
	if (c == '"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
	else if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
}

static int	check_dollar_in_quotes(char *str)
{
	int	i;
	int	in_dquote;
	int	in_squote;
	int	dollar_in_quotes;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	dollar_in_quotes = 0;
	while (str[i])
	{
		update_quote_state(str[i], &in_dquote, &in_squote);
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			if (in_dquote || in_squote)
				dollar_in_quotes = 1;
		}
		i++;
	}
	return (dollar_in_quotes);
}

int	check_is_retokenizable(char *str)
{
	int	i;
	int	found_quote;

	i = 0;
	found_quote = 0;
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
				found_quote = 1;
			i++;
		}
	}
	if (ft_strchr(str, '$') && !found_quote)
		return (1);
	if (!has_quotes_and_dollars(str))
		return (0);
	return (!check_dollar_in_quotes(str));
}
