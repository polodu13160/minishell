/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:00:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/04 17:56:43 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_2_fds(int *fd, int *fd2)
{
	ft_close(fd);
	ft_close(fd2);
}

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


