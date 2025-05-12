/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_full_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:41:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/12 15:07:36 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token.h"

static char	*init_quote_parsing(char *str, t_index *index, t_quote_state *state)
{
	char	*result;

	index->i = 0;
	index->j = 0;
	state->in_dquote = 0;
	state->in_squote = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) * 4 + 1));
	if (!result)
		return (NULL);
	return (result);
}

static void	handle_quotes(char *str, t_index *index, t_quote_state *state,
		char *result)
{
	if (str[index->i] == '"' && !state->in_squote)
	{
		state->in_dquote = !state->in_dquote;
		(index->i)++;
	}
	else if (str[index->i] == '\'' && !state->in_dquote)
	{
		state->in_squote = !state->in_squote;
		(index->i)++;
	}
	else if (str[index->i] == '"' || str[index->i] == '\'')
	{
		result[index->j++] = str[index->i++];
	}
}

static char	*extract_var_name(char *str, int *i, int *var_len)
{
	char	*var_name;

	*var_len = 0;
	(*i)++;
	while (str[*i + *var_len] && str[*i + *var_len] != ' ' && str[*i
			+ *var_len] != '"' && str[*i + *var_len] != '\'' && str[*i
			+ *var_len] != '$')
		(*var_len)++;
	var_name = ft_substr(str, *i, *var_len);
	return (var_name);
}

static void	process_env_var(char *str, char *result, t_index *index,
		t_minishell minishell)
{
	char	*var_name;
	char	*value;
	int		var_len;
	int		k;

	var_name = extract_var_name(str, &(index->i), &var_len);
	value = get_env_value(var_name, minishell.env);
	free(var_name);
	k = 0;
	while (value && value[k])
		result[(index->j)++] = value[k++];
	free(value);
	index->i += var_len;
}

char	*parse_quotes(char *str, t_minishell minishell)
{
	t_index			index;
	t_quote_state	state;
	char			*result;

	result = init_quote_parsing(str, &index, &state);
	if (!result)
		return (NULL);
	while (str[index.i])
	{
		if (str[index.i] == '"' || str[index.i] == '\'')
			handle_quotes(str, &index, &state, result);
		else if (str[index.i] == '$' && !state.in_squote)
			process_env_var(str, result, &index, minishell);
		else
			result[index.j++] = str[index.i++];
	}
	result[index.j] = '\0';
	free(str);
	return (result);
}
