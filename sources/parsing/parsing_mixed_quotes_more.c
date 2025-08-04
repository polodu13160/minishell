/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mixed_quotes_more.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:50 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 16:23:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
# include <stdlib.h>

void	append_value_to_result(char *result, char *value, int *j)
{
	int	k;

	if (!value)
		return ;
	k = 0;
	while (value[k])
		result[(*j)++] = value[k++];
	free(value);
}

void	handle_special_var(char *str, char *result, t_expand_data *data)
{
	char	special[2];
	char	*value;

	special[0] = str[data->i];
	special[1] = '\0';
	value = get_env_value(special, data->minishell);
	append_value_to_result(result, value, &data->j);
	data->i++;
}

void	shift_token(t_token *token, int i)
{
	free(token[i].value);
	while (token[i + 1].type != T_NULL)
	{
		token[i] = token[i + 1];
		i++;
	}
	token[i].value = NULL;
	token[i].type = T_NULL;
}
