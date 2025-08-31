/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:06:18 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:04:18 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

int	init_pipex(t_minishell *minishell, int count_pipee)
{
	int	i;

	i = 0;
	minishell->pipex = ft_calloc(minishell->count_pipee + 2, sizeof(t_pipex));
	if (minishell->pipex == NULL)
	{
		perror("Error Malloc");
		return (1);
	}
	while (i <= count_pipee)
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
	int	limit_pipee;

	limit_pipee = 0;
	minishell->count_pipee = count_pipee(tokens);
	if (init_pipex(minishell, minishell->count_pipee) == 1)
		return (1);
	while (limit_pipee <= count_pipee(tokens))
	{
		minishell->pipex[limit_pipee].init = 0;
		minishell->pipex[limit_pipee].infiles = store_infiles(tokens,
				limit_pipee);
		minishell->pipex[limit_pipee].outfiles = store_outfiles(tokens,
				limit_pipee);
		minishell->pipex[limit_pipee].cmd = store_cmd(tokens, limit_pipee);
		if (minishell->pipex[limit_pipee].infiles == NULL
			|| minishell->pipex[limit_pipee].outfiles == NULL
			|| minishell->pipex[limit_pipee].cmd == NULL)
		{
			perror("Error Malloc");
			return (1);
		}
		limit_pipee++;
	}
	return (0);
}
