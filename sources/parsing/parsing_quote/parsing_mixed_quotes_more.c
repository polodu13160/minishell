/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mixed_quotes_more.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:50 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:36:21 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
#include "stdlib.h"

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
