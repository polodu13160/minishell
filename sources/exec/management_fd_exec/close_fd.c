/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:38:41 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/20 03:48:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"

void	close_other_here_doc(t_minishell *minishell, t_pipe exec, int index)
{
	int	j;

	while (minishell->pipex[++index].infiles != NULL)
	{
		j = 0;
		while (minishell->pipex[index].infiles[j].value)
		{
			if (minishell->pipex[index].infiles[j].type == T_HEREDOC)
			{
				if (exec.fd_infile.fd != minishell->pipex[index].infiles[j].fd
					&& exec.fd_outfile.fd != minishell->pipex[index].infiles[j].fd)
					ft_close(&minishell->pipex[index].infiles[j].fd);
				else
					minishell->pipex[index].infiles[j].fd = -1;
			}
			j++;
		}
	}
}

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
