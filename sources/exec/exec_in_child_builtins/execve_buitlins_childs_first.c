/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_buitlins_childs_first.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:19:17 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "use_free.h"
#include "unistd.h"

static int	ft_execve_first_builtin(t_minishell *minishell, t_pipe *exec)
{
	if (close_and_dup(exec) == 8)
		return (8);
	if (minishell->pipex[0].cmd[0] != NULL
		&& minishell->pipex[0].cmd[0][0] != '\0')
	{
		return (apply_builtins(minishell, 0, exec, 0));
	}
	else
		return (127);
}

int	execve_builtin_first(t_minishell *minishell, t_pipe *exec)
{
	pid_t	pid;
	int		return_exec;

	pid = fork();
	if (pid == -1)
		error_fork_or_pipe(exec, minishell, exec->pipe, 0);
	return_exec = 1;
	minishell->pids[0] = pid;
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = ft_execve_first_builtin(minishell, exec);
		if (exec->fd_infile.value == NULL && exec->fd_infile.type != t_pipeE)
			ft_close(&exec->fd_infile.fd);
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_outfile.type != t_pipeE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish_child(minishell, exec, return_exec);
	}
	return (return_exec);
}
