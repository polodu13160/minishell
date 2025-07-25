/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:09:40 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/01 17:44:14 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "builtins.h"

void	ft_init_exec_loop(t_pip *exec)
{
	exec->error = 0;
	exec->fd_infile.value = NULL;
	exec->fd_infile.type = T_NULL;
	exec->fd_outfile.type = T_NULL;
	exec->fd_outfile.value = NULL;
	exec->fd_infile.fd = -1;
	exec->fd_outfile.fd = -1;
}

static int	ft_execve_first_child(t_minishell *minishell, t_pip *exec)
{
	int	test_acces;

	if (ft_close_and_dup(exec) == 8)
		return (8);
	if (minishell->pipex[0].cmd[0] != NULL
		&& minishell->pipex[0].cmd[0][0] != '\0')
	{
		test_acces = access(minishell->pipex[0].cmd[0], F_OK);
		if (test_acces == 0 && ft_strchr(minishell->pipex[0].cmd[0], '/') != 0)
		{
			execve(minishell->pipex[0].cmd[0], minishell->pipex[0].cmd,
				exec->env);
			return (126);
		}
		else
			return (ft_exec_to_env(minishell, exec, 0, 0));
	}
	else
		return (127);
	return (127);
}

static int	ft_execve_finish(t_minishell *minishell, t_pip *exec, int *new_pipe,
		int i)
{
	int	test_acces;

	if (ft_close_and_dup_last(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL
		&& minishell->pipex[i].cmd[0][0] != '\0')
	{
		test_acces = access(minishell->pipex[i].cmd[0], F_OK);
		if (test_acces == 0 && ft_strchr(minishell->pipex[i].cmd[0], '/') != 0)
		{
			execve(minishell->pipex[i].cmd[0], minishell->pipex[i].cmd,
				exec->env);
			return (126);
		}
		else
			return (ft_exec_to_env(minishell, exec, 0, i));
	}
	else
		return (127);
	return (127);
}

int	ft_execve_next(t_minishell *minishell, t_pip *exec, int i, int return_exec)
{
	pid_t	pid;
	int		new_pipe[2];

	if (pipe(new_pipe) < 0)
		return (1);
	pid = fork();
	minishell->pids[i] = pid;
	if (pid == -1)
		error_fork(exec, minishell, NULL);
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = ft_execve_finish(minishell, exec, new_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close_pip(exec, new_pipe, 0);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		ft_finish_child(minishell, exec, return_exec);
	}
	else
		ft_close_pip(exec, new_pipe, 1);
	return (0);
}

int	ft_execve_first(t_minishell *minishell, t_pip *exec)
{
	pid_t	pid;
	int		return_exec;

	pid = fork();
	return_exec = 1;
	minishell->pids[0] = pid;
	if (pid == -1)
		error_fork(exec, minishell, NULL);
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = ft_execve_first_child(minishell, exec);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		ft_finish_child(minishell, exec, return_exec);
	}
	return (return_exec);
}
