/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:38:41 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"

void	close_2_fds(int *fd, int *fd2)
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

void	close_pip(t_pipe *exec, int *new_pipe, int substitue)
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
