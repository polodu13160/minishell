/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:22:08 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:37:32 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

char	*prepare_string_for_quote_check(char *str)
{
	char	*temp;

	temp = NULL;
	if (str[0] == '$')
	{
		temp = ft_strdup(str);
		free(str);
		return (temp);
	}
	temp = ft_strdup(str);
	free(str);
	return (temp);
}

char	*allocate_quote_copy(char *str)
{
	char	*copy;

	copy = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!copy)
	{
		free(str);
		return (NULL);
	}
	return (copy);
}

void	handle_single_quote_tokenize(int *i, int *inside_squotes,
		int inside_dquotes)
{
	if (!inside_dquotes && !*inside_squotes)
		*inside_squotes = 1;
	else if (*inside_squotes && !inside_dquotes)
		*inside_squotes = 0;
	(*i)++;
}

void	handle_double_quote_tokenize(int *i, int *inside_dquotes,
		int inside_squotes)
{
	if (!inside_squotes && !*inside_dquotes)
		*inside_dquotes = 1;
	else if (*inside_dquotes && !inside_squotes)
		*inside_dquotes = 0;
	(*i)++;
}

void	process_quote_character(char *str, char *copy, t_quote_state *state,
		t_index *index)
{
	if (str[index->i] == '\'' && !state->in_dquote && !state->in_squote)
		handle_single_quote_tokenize(&index->i, &state->in_squote,
			state->in_dquote);
	else if (str[index->i] == '\'' && state->in_squote && !state->in_dquote)
		handle_single_quote_tokenize(&index->i, &state->in_squote,
			state->in_dquote);
	else if (str[index->i] == '"' && !state->in_squote && !state->in_dquote)
		handle_double_quote_tokenize(&index->i, &state->in_dquote,
			state->in_squote);
	else if (str[index->i] == '"' && state->in_dquote && !state->in_squote)
		handle_double_quote_tokenize(&index->i, &state->in_dquote,
			state->in_squote);
	else if (str[index->i] == '$' && (str[index->i + 1] == '\'' || str[index->i
				+ 1] == '"') && (state->in_dquote || state->in_squote))
		index->i++;
	else
		copy[index->j++] = str[index->i++];
}
