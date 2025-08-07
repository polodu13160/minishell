/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:31:36 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 16:06:56 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

int	count_infiles(t_token *tokens, int limit_pipe)
{
	int	count_infiles;
	int	i;
	int	count_pipe;

	count_infiles = 0;
	i = 0;
	count_pipe = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe)
				count_infiles++;
		}
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
				count_infiles++;
		i++;
	}
	return (count_infiles);
}

void	join_tab_infiles_ext(t_token *tokens, int i)
{
	if (tokens[i].type == T_REDIRECT_IN)
	{
		free(tokens[i].value);
		tokens[i].value = tokens[i + 1].value;
	}
}

int	join_tab_infiles(t_token *tokens, int limit_pipe, t_token *malloc_infiles,
		int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			if ((++count_pipe) == limit_pipe)
				malloc_infiles[j++] = tokens[i];
		}
		else if (count_pipe == limit_pipe)
		{
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
			{
				join_tab_infiles_ext(tokens, i);
				if (tokens[i + 1].type == T_AMBIGOUS)
					tokens[i].type = T_AMBIGOUS;
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_infiles[j++] = tokens[i];
			}
		}
	}
	return (j);
}

t_token	*store_infiles(t_token *tokens, int limit_pipe)
{
	int		i_count_infiles;
	int		last_index_malloc_infiles;
	t_token	*malloc_infiles;
	int		i;

	i = 0;
	i_count_infiles = count_infiles(tokens, limit_pipe);
	malloc_infiles = ft_calloc(i_count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	last_index_malloc_infiles = join_tab_infiles(tokens, limit_pipe,
			malloc_infiles, 0);
	malloc_infiles[last_index_malloc_infiles].value = NULL;
	i = 0;
	return (malloc_infiles);
}
