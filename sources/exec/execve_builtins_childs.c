/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins_childs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:04:37 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/05 02:10:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "use_free.h"
#include "unistd.h"

static int	ft_execve_first_builtin(t_minishell *minishell, t_pip *exec)
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

int	execve_builtin_first(t_minishell *minishell, t_pip *exec)
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
		if (exec->fd_infile.value == NULL && exec->fd_infile.type != T_PIPE)
			ft_close(&exec->fd_infile.fd);
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish_child(minishell, exec, return_exec);
	}
	return (return_exec);
}

static int	ft_execve_finish_builtin(t_minishell *minishell, t_pip *exec,
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

int	execve_builtin_next(t_minishell *minishell, t_pip *exec, int i,
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
		finish_child(minishell, exec, return_exec);
	}
	else
		close_pip(exec, n_pipe, 1);
	return (0);
}
