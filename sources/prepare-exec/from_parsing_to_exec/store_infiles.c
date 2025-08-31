/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:31:36 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:05:08 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>
#include "libft.h"

int	count_infiles(t_token *tokens, int limit_pipee)
{
	int	count_infiles;
	int	i;
	int	count_pipee;

	count_infiles = 0;
	i = 0;
	count_pipee = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipee++;
			if (count_pipee == limit_pipee)
				count_infiles++;
		}
		else if (count_pipee > limit_pipee)
			break ;
		else if (count_pipee == limit_pipee)
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

int	join_tab_infiles(t_token *tokens, int limit_pipee, t_token *malloc_infiles,
		int count_pipee)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			if ((++count_pipee) == limit_pipee)
				malloc_infiles[j++] = tokens[i];
		}
		else if (count_pipee == limit_pipee)
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

t_token	*store_infiles(t_token *tokens, int limit_pipee)
{
	int		i_count_infiles;
	int		last_index_malloc_infiles;
	t_token	*malloc_infiles;
	int		i;

	i = 0;
	i_count_infiles = count_infiles(tokens, limit_pipee);
	malloc_infiles = ft_calloc(i_count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	last_index_malloc_infiles = join_tab_infiles(tokens, limit_pipee,
			malloc_infiles, 0);
	malloc_infiles[last_index_malloc_infiles].value = NULL;
	i = 0;
	return (malloc_infiles);
}
