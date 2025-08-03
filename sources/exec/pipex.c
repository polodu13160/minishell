/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/03 16:57:37 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "pipex.h"
#include "token.h"
#include <sys/wait.h>

void	init_exec(t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error = 0;
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	exec->path_args = NULL;
	exec->env = env;
	exec->fd_infile.value = NULL;
	exec->fd_infile.fd = -1;
	exec->fd_outfile.value = NULL;
	exec->fd_outfile.fd = -1;
}

int	ft_wait_child(t_minishell *minishell)
{
	int		statuetemp;
	pid_t	pidvalue;
	int		status;
	int		pid;

	status = 0;
	pid = minishell->pids[minishell->count_pipe];
	while (pid == -1)
	{
		minishell->count_pipe--;
		pid = minishell->pids[minishell->count_pipe];
	}
	pidvalue = wait(&statuetemp);
	while (pidvalue > 0)
	{
		ft_message_output(statuetemp, minishell, pidvalue);
		if (pidvalue == pid)
			status = statuetemp;
		pidvalue = wait(&statuetemp);
	}
	if (WIFSIGNALED(status))
		minishell->return_command = 128 + WTERMSIG(status);
	else
		minishell->return_command = WEXITSTATUS(status);
	return (status);
}

void	ft_no_perm_child(t_minishell *minishell, t_pip *exec, int i)
{
	int	pid;

	pid = fork();
	minishell->pids[i] = pid;
	if (pid == 0)
	{
		setup_signals_child();
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		ft_finish_child(minishell, exec, 1);
	}
}

void	ft_loop_pipe(t_minishell *minishell, t_pip *exec, int i)
{
	while (++i <= minishell->count_pipe)
	{
		if (ft_check_perm(exec, minishell, i) == 0)
		{
			if (check_builtins(minishell, i) == 1)
			{
				if (i == 0)
					ft_execve_builtin_first(minishell, exec);
				else
					ft_execve_builtin_next(minishell, exec, i, 1);
			}
			else if (i == 0)
				ft_execve_first(minishell, exec);
			else if (i > 0)
				ft_execve_next(minishell, exec, i, 1);
			if (exec->fd_infile.type != T_PIPE)
				ft_close(&exec->fd_infile.fd);
			if (exec->fd_outfile.type != T_PIPE)
				ft_close(&exec->fd_outfile.fd);
		}
		else
			ft_no_perm_child(minishell, exec, i);
	}
	ft_close(&exec->pipe[0]);
	ft_close(&exec->pipe[1]);
}

int	ft_pipex(t_minishell *minishell)
{
	t_pip	exec;
	int		status;

	status = 0;
	init_exec(&exec, minishell->env);
	if (check_builtins(minishell, 0) != 0 && minishell->count_pipe == 0)
	{
		status = message_output_no_child(ft_execve_builtin_no_child(minishell,
					&exec, 0, 0), minishell);
		return (status);
	}
	minishell->pids = ft_calloc(minishell->count_pipe + 1, sizeof(pid_t));
	if (minishell->pids == NULL)
		return (ft_putstr_fd("Error Malloc\n", 2));
	if (ft_set_path_env(&exec, minishell->env) == 1)
		return (ft_finish(&exec, minishell, status, "Error Malloc"));
	if (pipe(exec.pipe) == -1)
		return (ft_finish(&exec, minishell, status, "Error pipe"));
	rl_event_hook = in_process_marker;
	ft_loop_pipe(minishell, &exec, -1);
	ft_wait_child(minishell);
	status = minishell->return_command;
	rl_event_hook = NULL;
	ft_finish(&exec, minishell, status, NULL);
	return (0);
}
