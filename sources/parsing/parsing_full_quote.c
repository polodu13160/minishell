/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_full_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:41:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 16:22:46 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token.h"
#include "builtins.h"

static void	handle_quotes(char *str, t_index *index, t_quote_state *state)
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
	else
		(index->i)++;
}

char	*extract_var_name(char *str, int *i, int *var_len)
{
	char	*var_name;

	*var_len = 0;
	(*i)++;
	while (str[*i + *var_len] && str[*i + *var_len] != ' ' && str[*i
			+ *var_len] != '"' && str[*i + *var_len] != '\'' && str[*i
			+ *var_len] != '$' && str[*i + *var_len] != '/' && str[*i
			+ *var_len] != ':')
		(*var_len)++;
	var_name = ft_substr(str, *i, *var_len);
	return (var_name);
}

int	process_env_var(char *str, char *result, t_index *index,
		t_minishell *minishell)
{
	char	*var_name;
	char	*value;
	int		var_len;
	int		k;

	var_name = extract_var_name(str, &(index->i), &var_len);
	if (var_name == NULL)
		return 1;
	value = get_env_value(var_name, minishell);
	free(var_name);
	if (!value)
	{
		index->i += var_len;
		return (0);
	}
	k = 0;
	while (value && value[k])
		result[(index->j)++] = value[k++];
	free(value);
	index->i += var_len;
	return (0);
}

void	check_state_quote(char *str, t_quote_state *state, t_index *index,
		char *result)
{
	if (str[index->i] == '\\' && state->in_dquote && str[index->i + 1])
	{
		if (str[index->i + 1] == '$' || str[index->i + 1] == '"' || str[index->i
				+ 1] == '\\' || str[index->i + 1] == '`')
		{
			result[index->j++] = str[index->i + 1];
			index->i += 2;
		}
		else
			result[index->j++] = str[index->i++];
	}
}

int	parse_quote_loop(char *str, t_minishell *minishell, t_index *index,
		char *result)
{
	t_quote_state	state;

	state.in_dquote = 0;
	state.in_squote = 0;
	while (str[index->i])
	{
		if (str[index->i] == '\\' && state.in_dquote && str[index->i + 1])
			check_state_quote(str, &state, index, result);
		else if (str[index->i] == '$' && !state.in_squote)
		{
			if (process_env_var(str, result, index, minishell))
			{
				perror("Error Malloc");
				free(result);
				free(str);
				return (1);
			}
		}
		else if ((str[index->i] == '"' && !state.in_squote) || (str[index->i] == '\'' && !state.in_dquote))
			handle_quotes(str, index, &state);
		else
			result[index->j++] = str[index->i++];
	}
	return (0);
}
