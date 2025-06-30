/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:00:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/18 20:33:24 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"

int	ft_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
		{
			return (-1);
		}
		*fd = -1;
	}
	return (0);
}

void	ft_close_pip(t_pip *exec, int *new_pipe, int substitue)
{
	ft_close(&exec->pipe[0]);
	ft_close(&exec->pipe[1]);
	if (substitue == 1)
	{
		exec->pipe[0] = new_pipe[0];
		exec->pipe[1] = new_pipe[1];
	}
	else
	{
		if (new_pipe != NULL)
		{
			ft_close(&new_pipe[0]);
			ft_close(&new_pipe[1]);
		}
	}
}

int	count_pipe(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == T_PIPE)
			count++;
		i++;
	}
	return (count);
}

void	unlink_here_doc(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->tokens[i].value)
	{
		if (minishell->tokens[i].type == T_HEREDOC)
		{
			if (ft_strncmp("/tmp", minishell->tokens[i].value, 4) == 0)
				unlink(minishell->tokens[i].value);
		}
		i++;
	}
}
