/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:06:18 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 01:17:24 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>

int	init_pipex(t_minishell *minishell, int count_pipe)
{
	int	i;

	i = 0;
	minishell->pipex = ft_calloc(minishell->count_pipe + 2, sizeof(t_pipex));
	if (minishell->pipex == NULL)
	{
		perror("Error Malloc");
		return (1);
	}
	while (i <= count_pipe)
	{
		minishell->pipex[i].init = 0;
		minishell->pipex[i].infiles = NULL;
		minishell->pipex[i].outfiles = NULL;
		minishell->pipex[i].cmd = NULL;
		i++;
	}
	minishell->pipex[i].init = 1;
	return (0);
}

int	prepare_to_pipex(t_minishell *minishell, t_token *tokens)
{
	int	limit_pipe;

	limit_pipe = 0;
	minishell->count_pipe = count_pipe(tokens);
	if (init_pipex(minishell, minishell->count_pipe) == 1)
		return (1);
	while (limit_pipe <= count_pipe(tokens))
	{
		minishell->pipex[limit_pipe].init = 0;
		minishell->pipex[limit_pipe].infiles = store_infiles(tokens,
				limit_pipe);
		minishell->pipex[limit_pipe].outfiles = store_outfiles(tokens,
				limit_pipe);
		minishell->pipex[limit_pipe].cmd = store_cmd(tokens, limit_pipe);
		if (minishell->pipex[limit_pipe].infiles == NULL
			|| minishell->pipex[limit_pipe].outfiles == NULL
			|| minishell->pipex[limit_pipe].cmd == NULL)
		{
			perror("Error Malloc");
			return (1);
		}
		limit_pipe++;
	}
	return (0);
}
