/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:06:18 by pde-petr          #+#    #+#             */
/*   Updated: 2025/09/10 15:27:02 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

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
	int	limit_pipe;

	limit_pipe = 0;
	minishell->count_pipee = count_pipee(tokens);
	if (init_pipex(minishell, minishell->count_pipee) == 1)
		return (1);
	while (limit_pipe <= count_pipee(tokens))
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
