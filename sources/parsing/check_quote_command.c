/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:22:08 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/27 19:22:31 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*prepare_string_for_quote_check(char *str)
{
	if (str[0] == '$')
		str = ft_strtrim(str, "$");
	return (str);
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

void	handle_single_quote(int *i, int *inside_squotes, int inside_dquotes)
{
	if (!inside_dquotes && !*inside_squotes)
		*inside_squotes = 1;
	else if (*inside_squotes && !inside_dquotes)
		*inside_squotes = 0;
	(*i)++;
}

void	handle_double_quote(int *i, int *inside_dquotes, int inside_squotes)
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
		handle_single_quote(&index->i, &state->in_squote, state->in_dquote);
	else if (str[index->i] == '\'' && state->in_squote && !state->in_dquote)
		handle_single_quote(&index->i, &state->in_squote, state->in_dquote);
	else if (str[index->i] == '"' && !state->in_squote && !state->in_dquote)
		handle_double_quote(&index->i, &state->in_dquote, state->in_squote);
	else if (str[index->i] == '"' && state->in_dquote && !state->in_squote)
		handle_double_quote(&index->i, &state->in_dquote, state->in_squote);
	else
		copy[index->j++] = str[index->i++];
}
