/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:35:38 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

char	*check_quote_command(char *str)
{
	char			*copy;
	t_quote_state	state;
	t_index			index;

	str = prepare_string_for_quote_check(str);
	copy = allocate_quote_copy(str);
	if (!copy)
		return (NULL);
	state.in_squote = 0;
	state.in_dquote = 0;
	index.i = 0;
	index.j = 0;
	while (str[index.i])
		process_quote_character(str, copy, &state, &index);
	copy[index.j] = '\0';
	free(str);
	return (copy);
}

char	*parse_env(char *str, t_minishell *minishell, int is_in_double)
{
	char	*result;
	size_t	needed_size;

	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	if (needed_size == 1)
	{
		result = ft_strdup("$");
		if (!result)
		{
			free(str);
			return (NULL);
		}
		free(str);
		return (result);
	}
	result = ft_calloc(sizeof(char), needed_size);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	result = parse_env_loop(str, minishell, result, is_in_double);
	return (result);
}
