/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:21:44 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:33:30 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_tokens_array(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens[count].type != T_NULL)
		count++;
	return (count);
}

int	count_new_tokens(t_token *new_tokens)
{
	int	count;

	count = 0;
	while (new_tokens[count].type != T_NULL)
		count++;
	return (count);
}

void	copy_tokens_before(t_token *result, t_token *tokens, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		result[j] = tokens[j];
		j++;
	}
}

void	copy_new_tokens(t_token *result, t_token *new_tokens, int start,
		int nb_new)
{
	int	k;

	k = 0;
	while (k < nb_new)
	{
		result[start + k] = new_tokens[k];
		k++;
	}
}

void	copy_tokens_after(t_token *result, t_token *tokens, int i,
		t_retokenize_data *data)
{
	int	k;

	k = i + 1;
	while (k < data->old_count)
	{
		result[data->insert_pos + data->nb_new + k - (i + 1)] = tokens[k];
		k++;
	}
	result[data->old_count + data->nb_new - 1].type = T_NULL;
}
