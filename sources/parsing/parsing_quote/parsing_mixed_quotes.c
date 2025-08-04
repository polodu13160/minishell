/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mixed_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:37:44 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 16:23:37 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
# include <stdlib.h>

void	handle_env_variable(char *str, char *result, t_expand_data *data)
{
	int		var_start;
	char	*var_name;
	char	*value;

	var_start = data->i;
	while (str[data->i] && (ft_isalnum(str[data->i]) || str[data->i] == '_'))
		data->i++;
	var_name = ft_substr(str, var_start, data->i - var_start);
	value = get_env_value(var_name, data->minishell);
	append_value_to_result(result, value, &data->j);
	free(var_name);
}

static void	handle_special_variable(char *str, char *result,
		t_expand_data *data)
{
	char	special[2];
	char	*value;

	special[0] = str[data->i];
	special[1] = '\0';
	value = get_env_value(special, data->minishell);
	append_value_to_result(result, value, &data->j);
	data->i++;
}

static void	process_dollar_sign(char *str, char *result, t_expand_data *data)
{
	data->i++;
	if (str[data->i] == '?' || str[data->i] == '$')
		handle_special_variable(str, result, data);
	else if (ft_isalnum(str[data->i]) || str[data->i] == '_')
		handle_env_variable(str, result, data);
	else
		result[data->j++] = '$';
}

static void	process_character(char *str, char *result, t_expand_data *data)
{
	if (str[data->i] == '"' && !data->in_squote)
	{
		data->in_dquote = !data->in_dquote;
		data->i++;
	}
	else if (str[data->i] == '\'' && !data->in_dquote)
	{
		data->in_squote = !data->in_squote;
		data->i++;
	}
	else if (str[data->i] == '$' && !data->in_squote)
		process_dollar_sign(str, result, data);
	else
		result[data->j++] = str[data->i++];
}

char	*parse_mixed_quotes(char *str, t_minishell *minishell)
{
	char			*result;
	size_t			needed_size;
	t_expand_data	data;

	data.i = 0;
	data.j = 0;
	data.in_dquote = 0;
	data.in_squote = 0;
	data.minishell = minishell;
	if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
		data.i = 1;
	needed_size = calculate_needed_size(str, minishell, 0, ft_strlen(str));
	result = ft_calloc(needed_size + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str[data.i])
		process_character(str, result, &data);
	result[data.j] = '\0';
	free(str);
	return (result);
}
