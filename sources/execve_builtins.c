/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:06:15 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/16 15:44:04 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "pipex.h"
#include "token.h"

static int	error_dup2_execve_builtin_no_child(t_pip *exec)
{
	ft_close(&exec->fd_infile.fd);
	ft_close(&exec->fd_outfile.fd);
	return (8);
}

int	ft_execve_builtin_no_child(t_minishell *minishell, t_pip *exec,
		int dup_redirect_in, int dup_redirect_out)
{
	dup_redirect_in = dup(0);
	dup_redirect_out = dup(1);
	if (ft_check_perm(exec, minishell, 0) == 0)
	{
		if (exec->fd_infile.fd != -1)
		{
			if (dup2(exec->fd_infile.fd, 0) == -1)
				return (error_dup2_execve_builtin_no_child(exec));
			ft_close(&exec->fd_infile.fd);
		}
		if (exec->fd_outfile.fd != -1)
		{
			if (dup2(exec->fd_outfile.fd, 1) == -1)
				return (error_dup2_execve_builtin_no_child(exec));
			ft_close(&exec->fd_outfile.fd);
		}
		apply_builtins(minishell, 0, exec);
		if (dup2(dup_redirect_in, 0) == -1 || dup2(dup_redirect_out, 1) \
		== -1)
			return (error_dup2_execve_builtin_no_child(exec));
		return (0);
	}
	return (1);
}

static int	ft_execve_finish(t_minishell *minishell, t_pip *exec, int *new_pipe,
		int i)
{
	if (ft_close_and_dup_finish(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		return (0);
	}
	return (apply_builtins(minishell, i, exec));
}

int	ft_execve_builtin(t_minishell *minishell, t_pip *exec, int i)
{
	pid_t	pid;
	int		new_pipe[2];
	int		return_exec;

	if (pipe(new_pipe) < 0)
		return (1);
	pid = fork();
	return_exec = 1;
	minishell->pids[i] = pid;
	if (pid == 0)
	{
		if (exec->error == 0)
			return_exec = ft_execve_finish(minishell, exec, new_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close_pip(exec, new_pipe, 0);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish(exec, minishell, 5);
		exit(return_exec);
	}
	else
		ft_close_pip(exec, new_pipe, 1);
	return (0);
}
