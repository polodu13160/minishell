/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize_final.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:13:45 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/27 19:13:54 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	insert_split_tokens(t_token *new_tokens, char **split, int start,
		int nb_new)
{
	int	k;

	k = 0;
	while (k < nb_new)
	{
		new_tokens[start + k].value = split[k];
		new_tokens[start + k].type = T_WORD;
		new_tokens[start + k].option = NULL;
		k++;
	}
}

static void	copy_tokens_after(t_token *new_tokens, t_token *tokens, int i,
		t_retokenize_data *data)
{
	int	k;

	k = i + 1;
	while (k < data->old_count)
	{
		new_tokens[data->insert_pos + data->nb_new + k - (i + 1)] = tokens[k];
		k++;
	}
	new_tokens[data->old_count + data->nb_new - 1].type = T_NULL;
}

static void	finalize_retokenize(t_token *tokens, t_token *new_tokens,
		t_minishell *minishell, int i)
{
	free(tokens[i].value);
	free(tokens);
	minishell->tokens = new_tokens;
}

int	retokenize(t_token *tokens, t_minishell *minishell, int i)
{
	t_retokenize_data	data;
	char				**split;
	t_token				*new_tokens;

	data.old_count = count_tokens_array(tokens);
	split = split_token_value(tokens[i].value, &data.nb_new);
	if (!split)
		return (1);
	new_tokens = allocate_new_tokens(data.old_count, data.nb_new, split);
	if (!new_tokens)
		return (1);
	data.insert_pos = i;
	copy_tokens_before(new_tokens, tokens, i);
	insert_split_tokens(new_tokens, split, i, data.nb_new);
	copy_tokens_after(new_tokens, tokens, i, &data);
	finalize_retokenize(tokens, new_tokens, minishell, i);
	free(split);
	return (0);
}
