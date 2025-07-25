/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:24:02 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 15:53:31 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_is_forbid(char *str, int i)
{
	if (!ft_strncmp(str, "\"", ft_strlen(str)))
	{
		
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
		{
			ft_putstr_fd("make sure to not use more than 2 >> or <<\n", 2);
			return (1);
		}
	}
	return (0);
}

static void	init_quote_counters(int *count_d, int *count_s, int *in_single,
		int *in_double)
{
	*count_d = 0;
	*count_s = 0;
	*in_single = 0;
	*in_double = 0;
}

static void	handle_double_quote(int *count_d, int *in_double, int in_single)
{
	if (!in_single)
	{
		(*count_d)++;
		*in_double = !(*in_double);
	}
}

static void	handle_single_quote(int *count_s, int *in_single, int in_double)
{
	if (!in_double)
	{
		(*count_s)++;
		*in_single = !(*in_single);
	}
}

int	count_quote(char *str)
{
	int	i;
	int	count_d;
	int	count_s;
	int	in_single;
	int	in_double;

	i = 0;
	init_quote_counters(&count_d, &count_s, &in_single, &in_double);
	while (str[i])
	{
		if (check_is_forbid(str, i))
			return (1);
		if (str[i] == '"')
			handle_double_quote(&count_d, &in_double, in_single);
		else if (str[i] == '\'')
			handle_single_quote(&count_s, &in_single, in_double);
		i++;
	}
	if (count_d % 2 != 0 || count_s % 2 != 0)
	{
		ft_putstr_fd("make sure to have quote in pairs\n", 1);
		return (1);
	}
	return (0);
}
