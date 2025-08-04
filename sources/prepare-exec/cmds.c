/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:10:03 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/04 22:11:58 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	count_cmd(t_token *tokens, int limit_pipe)
{
	int	i_count_command;
	int	i;
	int	count_pipe;

	i_count_command = 0;
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
				i_count_command++;
		i++;
	}
	return (i_count_command);
}

int	join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
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

char	**store_cmd(t_token *tokens, int limit_pipe)
{
	int		i_count_command;
	int		last_index_malloc_infiles;
	char	**malloc_cmd;

	i_count_command = count_cmd(tokens, limit_pipe);
	malloc_cmd = ft_calloc(i_count_command + 1, sizeof(char *));
	if (malloc_cmd == NULL)
		return (NULL);
	last_index_malloc_infiles = join_tab_cmd(tokens, limit_pipe, malloc_cmd,
			0);
	malloc_cmd[last_index_malloc_infiles] = NULL;
	return (malloc_cmd);
}
