/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:04:37 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/17 02:27:27 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "pipex.h"

static int	ft_execve_first_builtin(t_minishell *minishell, t_pip *exec)
{
	if (ft_close_and_dup(exec) == 8)
		return (8);
	if (minishell->pipex[0].cmd[0] != NULL
		&& minishell->pipex[0].cmd[0][0] != '\0')
	{
		return (apply_builtins(minishell, 0, exec, 0));
	}
	else
		return (127);
}

void	error_fork(t_pip *exec, t_minishell *minishell, int *new_pipe)
{
	ft_wait_child(minishell);
	if (exec->fd_infile.value == NULL && exec->fd_infile.type != T_PIPE)
		ft_close(&exec->fd_infile.fd);
	if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
		ft_close(&exec->fd_outfile.fd);
	ft_close_pip(exec, new_pipe, 0);
	ft_finish_child(minishell, exec, 1);
}

int	ft_execve_builtin_first(t_minishell *minishell, t_pip *exec)
{
	pid_t	pid;
	int		return_exec;

	pid = fork();
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
		ft_finish_child(minishell, exec, return_exec);
	}
	else if (pid == -1)
		error_fork(exec, minishell, NULL);
	return (return_exec);
}
