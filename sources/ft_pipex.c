/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 21:22:36 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "pipex.h"
#include "token.h"
#include <stdio.h>
#include <sys/wait.h>

void	init_exec(t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error = 0;
	exec->pipe[0] = 0;
	exec->pipe[1] = 1;
	exec->path_args = NULL;
	exec->env = env;
	exec->fd_infile.value = NULL;
	exec->fd_outfile.value = NULL;
}

static int	ft_wait_child(t_minishell *minishell)
{
	int		statuetemp;
	pid_t	pidvalue;
	int		status;
	int		pid;

	status = 0;
	pid = minishell->pids[minishell->count_pipe];
	pidvalue = wait(&statuetemp);
	while (pidvalue > 0)
	{
		message_output(statuetemp, minishell, pidvalue);
		if (pidvalue == pid)
			status = statuetemp;
		pidvalue = wait(&statuetemp);
	}
	return (status);
}

void	finish(t_pip *exec, t_minishell *minishell, int full)
{
	int	i;

	i = 0;
	if (exec != NULL && exec->path_args != NULL)
	{
		while (exec->path_args[i])
			free(exec->path_args[i++]);
		free(exec->path_args);
	}
	if (full > 1)
	{
		if (full == 2)
			return (free_pipex(minishell, 0));
		free_error(minishell->tokens, minishell, 0);
		if (full == 5)
		{
			if (minishell->env)
			{
				i = 0;
				while (minishell->env[i])
					free(minishell->env[i++]);
				free(minishell->env);
			}
		}
	}
}

void	ft_loop_pipe(t_minishell *minishell, t_pip *exec)
{
	int	i;

	i = 0;
	while (i <= minishell->count_pipe)
	{
		if (i != 0 && exec->fd_infile.fd != -1 && exec->fd_infile.value != NULL
			&& exec->fd_infile.type != T_PIPE)
			ft_close(&exec->fd_infile.fd);
		if (ft_check_perm(exec, minishell, i) == 0)
		{
			if (i == 0)
				ft_execve_first(minishell, exec);
			if (i > 0)
				ft_execve_next(minishell, exec, i);
			if (exec->fd_infile.type != T_PIPE)
				ft_close(&exec->fd_infile.fd);
			if (exec->fd_outfile.type != T_PIPE)
				ft_close(&exec->fd_outfile.fd);
		}
		i++;
	}
}

int	ft_pipex(t_minishell *minishell)
{
	t_pip	exec;
	int		status;

	init_exec(&exec, minishell->env);
	status = 0;
	minishell->pids = ft_calloc(minishell->count_pipe + 1, sizeof(pid_t));
	if (minishell->pids == NULL)
	{
		ft_putstr_fd("Error Malloc", 2);
		return (1);
	}
	if (ft_set_path_env(&exec, minishell->env) == 1)
		return (1);
	if (minishell->count_pipe == 0 && check_builtins(minishell->tokens, 0) )
	{
		apply_builtins(minishell->tokens, 0, minishell, &exec);
		return (0);
	}
	if (pipe(exec.pipe) == -1)
		return (1);
	ft_loop_pipe(minishell, &exec);
	ft_close(&exec.pipe[0]);
	ft_close(&exec.pipe[1]);
	status = WEXITSTATUS(ft_wait_child(minishell));
	minishell->return_command = status;
	finish(&exec, minishell, 0);
	return (0);
}
