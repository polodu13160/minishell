/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:52:53 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/27 19:14:22 by antbonin         ###   ########.fr       */
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

char	**split_token_value(char *value, int *nb_new)
{
	char	**split;

	split = ft_split(value, ' ');
	if (!split)
		return (NULL);
	*nb_new = 0;
	while (split[*nb_new])
		(*nb_new)++;
	return (split);
}

void	free_split_array(char **split)
{
	int	j;

	j = 0;
	while (split[j])
		free(split[j++]);
	free(split);
}

t_token	*allocate_new_tokens(int old_count, int nb_new, char **split)
{
	t_token	*new_tokens;

	new_tokens = ft_calloc(sizeof(t_token), old_count + nb_new);
	if (!new_tokens)
	{
		free_split_array(split);
		return (NULL);
	}
	return (new_tokens);
}

void	copy_tokens_before(t_token *new_tokens, t_token *tokens, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_tokens[j] = tokens[j];
		j++;
	}
}
