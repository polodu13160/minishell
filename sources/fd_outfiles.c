/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:52:59 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/05 18:00:46 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_count_outfiles(t_token *tokens, int limit_pipe)
{
	int	count_outfiles;
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	count_outfiles = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe + 1)
				count_outfiles++;
		}
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				count_outfiles++;
		i++;
	}
	return (count_outfiles);
}

void	ft_join_tab_outfiles_ext(t_token *tokens, int i,
		t_token *malloc_outfiles, int j)
{
	if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
	{
		free(tokens[i].value);
		tokens[i].value = ft_strdup(tokens[i + 1].value);
		tokens[i + 1].type = T_WORD_FOR_REDIRECT;
		malloc_outfiles[j++] = tokens[i];
	}
}

int	ft_join_tab_outfiles(t_token *tokens, int limit_pipe,
		t_token *malloc_outfiles, int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe + 1)
				malloc_outfiles[j++] = tokens[i];
		}
		else if (count_pipe == limit_pipe)
		{
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
			{
				free(tokens[i].value);
				tokens[i].value = ft_strdup(tokens[i + 1].value);
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_outfiles[j++] = tokens[i];
			}
		}
	}
	return (j);
}

t_token	*ft_store_outfiles(t_token *tokens, int limit_pipe)
{
	int		count_pipe;
	int		count_outfiles;
	int		last_index_malloc_outfiles;
	t_token	*malloc_outfiles;

	count_pipe = 0;
	count_outfiles = ft_count_outfiles(tokens, limit_pipe);
	malloc_outfiles = ft_calloc(count_outfiles + 1, sizeof(t_token));
	// printf("element, %d \n", count_outfiles);
	if (malloc_outfiles == NULL)
		return (NULL);
	last_index_malloc_outfiles = ft_join_tab_outfiles(tokens, limit_pipe,
			malloc_outfiles, 0);
	malloc_outfiles[last_index_malloc_outfiles].value = NULL;
	return (malloc_outfiles);
}
