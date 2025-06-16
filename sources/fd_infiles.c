/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_infiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:31:36 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/16 15:21:28 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_count_infiles(t_token *tokens, int limit_pipe)
{
	int	count_infiles;
	int	i;
	int	count_pipe;

	count_infiles = 0;
	i = 0;
	count_pipe = 0;
	while (tokens[i].value)
	{
		tokens[i].fd = -1;
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

void	ft_join_tab_infiles_ext(t_token *tokens, int i)
{
	if (tokens[i].type == T_REDIRECT_IN)
	{
		free(tokens[i].value);
		tokens[i].value = ft_strdup(tokens[i + 1].value);
	}
}

int	ft_join_tab_infiles(t_token *tokens, int limit_pipe,
		t_token *malloc_infiles, int count_pipe)
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
				ft_join_tab_infiles_ext(tokens, i);
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_infiles[j++] = tokens[i];
			}
		}
	}
	return (j);
}

t_token	*ft_store_infiles(t_token *tokens, int limit_pipe)
{
	int		count_infiles;
	int		last_index_malloc_infiles;
	t_token	*malloc_infiles;

	count_infiles = ft_count_infiles(tokens, limit_pipe);
	malloc_infiles = ft_calloc(count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	last_index_malloc_infiles = ft_join_tab_infiles(tokens, limit_pipe,
			malloc_infiles, 0);
	malloc_infiles[last_index_malloc_infiles].value = NULL;
	return (malloc_infiles);
}
