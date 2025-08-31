/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:38:41 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:58:30 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtins.h"
#include "readline/readline.h"
#include "unistd.h"

void	cleanup_here_doc_rl_clear_hist_and_reset_signal(t_minishell *mshell,
		t_pipe exec, int index)
{
	int	j;

	while (mshell->pipex[++index].infiles != NULL)
	{
		j = 0;
		while (mshell->pipex[index].infiles[j].value)
		{
			if (mshell->pipex[index].infiles[j].type == T_HEREDOC)
			{
				if (exec.fd_infile.fd != mshell->pipex[index].infiles[j].fd
					&& exec.fd_outfile.fd != mshell->pipex[index].infiles[j].fd)
					ft_close(&mshell->pipex[index].infiles[j].fd);
				else
					mshell->pipex[index].infiles[j].fd = -1;
			}
			j++;
		}
	}
	rl_clear_history();
	setup_signals_child();
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
