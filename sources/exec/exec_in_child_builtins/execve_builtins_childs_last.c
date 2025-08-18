/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins_childs_last.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:19:50 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/18 13:09:48 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "unistd.h"
#include "use_free.h"

static int	ft_execve_finish_builtin(t_minishell *minishell, t_pipe *exec,
		int *new_pipe, int i)
{
	ft_close(&exec->pipe[1]);
	if (close_and_dup_last(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		return (apply_builtins(minishell, i, exec, 0));
	}
	else
		return (0);
}

int	execve_builtin_next(t_minishell *minishell, t_pipe *exec, int i,
		int return_exec)
{
	pid_t	pid;
	int		n_pipe[2];

	if (pipe(n_pipe) < 0)
		error_fork_or_pipe(exec, minishell, NULL, 1);
	pid = fork();
	minishell->pids[i] = pid;
	if (pid == -1)
		error_fork_or_pipe(exec, minishell, n_pipe, 0);
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = ft_execve_finish_builtin(minishell, exec, n_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		close_pip(exec, n_pipe, 0);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		message_error_output(minishell, exec, return_exec,
			minishell->pipex[i].cmd[0]);
		finish_child(minishell, exec, return_exec);
	}
	close_pip(exec, n_pipe, 1);
	return (0);
}
