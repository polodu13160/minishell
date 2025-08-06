/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:13:45 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 17:22:39 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "use_free.h"
#include "parsing.h"
# include <stdlib.h>

static t_token	*tokenize_expanded_value(char *expanded_value)
{
	t_token	*new_tokens;
	int		count;

	count = count_tokens(expanded_value);
	if (count == 0)
		return (NULL);
	new_tokens = ft_calloc(sizeof(t_token), (count + 1));
	if (!new_tokens)
		return (NULL);
	init_data_token(new_tokens, count);
	if (count_quote(expanded_value))
	{
		free(new_tokens);
		return (NULL);
	}
	if (check_args(expanded_value, new_tokens, count))
		free_token(new_tokens);
	new_tokens[count].type = T_NULL;
	return (new_tokens);
}

static t_token	*prepare_retokenized_array(t_token *tokens, t_token *new_tokens,
		int i, t_retokenize_data *data)
{
	t_token	*result;

	data->old_count = count_tokens_array(tokens);
	data->nb_new = count_new_tokens(new_tokens);
	result = ft_calloc(sizeof(t_token), data->old_count + data->nb_new);
	if (!result)
		return (NULL);
	data->insert_pos = i;
	copy_tokens_before(result, tokens, i);
	copy_new_tokens(result, new_tokens, i, data->nb_new);
	copy_tokens_after(result, tokens, i, data);
	return (result);
}

static void	cleanup_and_assign(t_token *tokens, t_token *new_tokens,
		t_token *result, t_minishell *minishell)
{
	free(tokens);
	free(new_tokens);
	minishell->tokens = result;
}

static void	fix_pipe_types(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->tokens[i].type != T_NULL)
	{
		if (minishell->tokens[i].type == T_PIPE)
			minishell->tokens[i].type = T_WORD;
		i++;
	}
}

int	retokenize_expanded_token(t_token *tokens, t_minishell *minishell, int i)
{
	t_retokenize_data	data;
	t_token				*new_tokens;
	t_token				*result;

	(void)data;
	new_tokens = tokenize_expanded_value(tokens[i].value);
	if (!new_tokens)
		return (1);
	result = prepare_retokenized_array(tokens, new_tokens, i, &data);
	if (!result)
	{
		free_all(new_tokens, minishell, 0);
		return (1);
	}
	free(tokens[i].value);
	cleanup_and_assign(tokens, new_tokens, result, minishell);
	fix_pipe_types(minishell);
	return (0);
}
