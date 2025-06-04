/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:07:04 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 03:56:26 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_count_cmd(t_token *tokens, int limit_pipe)
{
	int	count_cmd;
	int	i;
	int	count_pipe;

	count_cmd = 0;
	i = 0;
	count_pipe = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				count_cmd++;
		i++;
	}
	return (count_cmd);
}

int	ft_join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
		int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				malloc_cmd[j++] = tokens[i].value;
	}
	return (j);
}

char	**ft_store_cmd(t_token *tokens, int limit_pipe)
{
	int		count_cmd;
	int		last_index_malloc_infiles;
	char	**malloc_cmd;

	count_cmd = ft_count_cmd(tokens, limit_pipe);
	malloc_cmd = ft_calloc(count_cmd + 1, sizeof(char *));
	if (malloc_cmd == NULL)
		return (NULL);
	last_index_malloc_infiles = ft_join_tab_cmd(tokens, limit_pipe, malloc_cmd,
			0);
	malloc_cmd[last_index_malloc_infiles] = NULL;
	return (malloc_cmd);
}
