/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_outfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:52:59 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:09:04 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>

int	count_outfiles(t_token *tokens, int limit_pipee)
{
	int	count_outfiles;
	int	i;
	int	count_pipee;

	i = 0;
	count_pipee = 0;
	count_outfiles = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == t_pipeE)
		{
			count_pipee++;
			if (count_pipee == limit_pipee + 1)
				count_outfiles++;
		}
		else if (count_pipee > limit_pipee)
			break ;
		else if (count_pipee == limit_pipee)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				count_outfiles++;
		i++;
	}
	return (count_outfiles);
}

void	join_tab_outfiles_ext(t_token *tokens, int i, t_token *malloc_outfiles,
		int j)
{
	free(tokens[i].value);
	tokens[i].value = tokens[i + 1].value;
	if (tokens[i + 1].type == T_AMBIGOUS)
		tokens[i].type = T_AMBIGOUS;
	tokens[i + 1].type = T_WORD_FOR_REDIRECT;
	malloc_outfiles[j] = tokens[i];
}

int	join_tab_outfiles(t_token *tokens, int limit_pipee,
		t_token *malloc_outfiles, int count_pipee)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == t_pipeE)
		{
			count_pipee++;
			if (count_pipee == limit_pipee + 1)
				malloc_outfiles[j++] = tokens[i];
		}
		else if (count_pipee == limit_pipee)
		{
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				join_tab_outfiles_ext(tokens, i, malloc_outfiles, j++);
		}
	}
	return (j);
}

t_token	*store_outfiles(t_token *tokens, int limit_pipee)
{
	int		count_pipee;
	int		i_count_outfiles;
	int		last_index_malloc_outfiles;
	t_token	*malloc_outfiles;

	count_pipee = 0;
	i_count_outfiles = count_outfiles(tokens, limit_pipee);
	malloc_outfiles = ft_calloc(i_count_outfiles + 1, sizeof(t_token));
	if (malloc_outfiles == NULL)
		return (NULL);
	last_index_malloc_outfiles = join_tab_outfiles(tokens, limit_pipee,
			malloc_outfiles, 0);
	malloc_outfiles[last_index_malloc_outfiles].value = NULL;
	return (malloc_outfiles);
}
