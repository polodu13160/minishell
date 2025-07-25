/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:06:15 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/17 21:24:32 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "pipex.h"
#include "token.h"

static int	error_dup2_execve_builtin_no_child(t_pip *exec, int dup_redirect_in,
		int dup_redirect_out)
{
	ft_close(&dup_redirect_in);
	ft_close(&dup_redirect_out);
	ft_close(&exec->fd_infile.fd);
	ft_close(&exec->fd_outfile.fd);
	return (8);
}

static int	dup_infile_and_outfile_builtin_no_child(t_pip *exec,
		int dup_redirect_in, int dup_redirect_out)
{
	if (exec->fd_infile.fd != -1)
	{
		if (dup2(exec->fd_infile.fd, 0) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		ft_close(&exec->fd_infile.fd);
	}
	if (exec->fd_outfile.fd != -1)
	{
		if (dup2(exec->fd_outfile.fd, 1) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		ft_close(&exec->fd_outfile.fd);
	}
	return (0);
}

int	ft_execve_builtin_no_child(t_minishell *minishell, t_pip *exec,
		int dup_redirect_in, int dup_redirect_out)
{
	if (ft_check_perm(exec, minishell, 0) == 0)
	{
		dup_redirect_in = dup(0);
		dup_redirect_out = dup(1);
		if (ft_strcmp(minishell->pipex[0].cmd[0], "exit") == 0)
		{
			ft_close_2_fds(&dup_redirect_in, &dup_redirect_out);
			ft_close_2_fds(&exec->fd_infile.fd, &exec->fd_outfile.fd);
		}
		else if (dup_infile_and_outfile_builtin_no_child(exec, dup_redirect_in,
				dup_redirect_out) == 8)
			return (8);
		minishell->return_command = apply_builtins(minishell, 0, exec, 1);
		if (dup2(dup_redirect_in, 0) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		if (dup2(dup_redirect_out, 1) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		ft_close_2_fds(&dup_redirect_in, &dup_redirect_out);
		return (minishell->return_command);
	}
	return (1);
}

static int	ft_execve_finish_builtin(t_minishell *minishell, t_pip *exec,
		int *new_pipe, int i)
{
	if (ft_close_and_dup_last(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		return (apply_builtins(minishell, i, exec, 0));
	}
	else
		return (0);
}

int	ft_execve_builtin_next(t_minishell *minishell, t_pip *exec, int i,
		int return_exec)
{
	pid_t	pid;
	int		n_pipe[2];

	if (pipe(n_pipe) < 0)
		return (1);
	pid = fork();
	minishell->pids[i] = pid;
	if (pid == -1)
		error_fork(exec, minishell, n_pipe);
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = ft_execve_finish_builtin(minishell, exec, n_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close_pip(exec, n_pipe, 0);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		ft_finish_child(minishell, exec, return_exec);
	}
	else
		ft_close_pip(exec, n_pipe, 1);
	return (0);
}
