/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_full_quote_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:04:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/28 19:05:14 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*init_quote_parsing(char *str, t_index *index)
{
	char	*result;

	index->i = 0;
	index->j = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(str) * 4 + 1));
	if (!result)
		return (NULL);
	return (result);
}

char	*parse_quotes(char *str, t_minishell *minishell)
{
	t_index	index;
	char	*result;

	result = init_quote_parsing(str, &index);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (parse_quote_loop(str, minishell, &index, result))
		return (NULL);
	result[index.j] = '\0';
	free(str);
	return (result);
}
