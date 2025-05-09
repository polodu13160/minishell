/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:24:02 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/09 15:23:32 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_is_forbid(char *str, int i)
{
	if ((str[i] == '\\' && str[i + 1] == '\\') || str[i] == ';'
		|| (str[i] == '|' && str[i + 1] == '|'))
	{
		ft_putstr_fd("forbidden preprocessor : || or && or ; or () or \\\n", 2);
		return (1);
	}
	else if ((str[i] == ')' && str[i + 1] == ')') || (str[i] == '(' && str[i
				+ 1] == ')'))
	{
		ft_putstr_fd("forbidden preprocessor : || or && or ; or () or \\\n", 2);
		return (1);
	}
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
	{
		ft_putstr_fd("make sur to not use more than 2 >> or <<\n", 2);
		return (1);
	}
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
	{
		ft_putstr_fd("make sur to not use more than 2 >> or <<\n", 2);
		return (1);
	}
	else
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
		if (check_is_forbid(str, i))
			return (1);
		if (str[i] == '"')
			count_d++;
		else if (str[i] == '\'')
			count_s++;
		i++;
	}
	if (count_d % 2 != 0 || count_s % 2 != 0)
	{
		ft_putstr_fd("make sur to have quote in pairs\n", 2);
		return (1);
	}
	return (0);
}
