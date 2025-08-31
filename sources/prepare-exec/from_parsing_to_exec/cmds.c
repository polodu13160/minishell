/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:10:03 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:02:30 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

int	count_cmd(t_token *tokens, int limit_pipee)
{
	int	i_count_command;
	int	i;
	int	count_pipee;

	i_count_command = 0;
	i = 0;
	count_pipee = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipee++;
		else if (count_pipee > limit_pipee)
			break ;
		else if (count_pipee == limit_pipee)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				i_count_command++;
		i++;
	}
	return (i_count_command);
}

int	join_tab_cmd(t_token *tokens, int limit_pipee, char **malloc_cmd,
		int count_pipee)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipee++;
		else if (count_pipee > limit_pipee)
			break ;
		else if (count_pipee == limit_pipee)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				malloc_cmd[j++] = tokens[i].value;
	}
	return (j);
}

char	**store_cmd(t_token *tokens, int limit_pipee)
{
	int		i_count_command;
	int		last_index_malloc_infiles;
	char	**malloc_cmd;

	i_count_command = count_cmd(tokens, limit_pipee);
	malloc_cmd = ft_calloc(i_count_command + 1, sizeof(char *));
	if (malloc_cmd == NULL)
		return (NULL);
	last_index_malloc_infiles = join_tab_cmd(tokens, limit_pipee, malloc_cmd,
			0);
	malloc_cmd[last_index_malloc_infiles] = NULL;
	return (malloc_cmd);
}
