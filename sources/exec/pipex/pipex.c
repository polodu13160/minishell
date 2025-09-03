/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/09/03 15:32:58 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "use_free.h"
#include <sys/wait.h>
#include <token.h>

void	init_exec(t_pipe *exec, char **env)
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

int	wait_child(t_minishell *minishell, int status, int pid, int coredumped)
{
	int		statuetemp;
	pid_t	pidvalue;

	coredumped = 0;
	pid = minishell->pids[minishell->count_pipee];
	minishell->count_pipee--;
	while (pid == -1 && minishell->count_pipee != -1)
	{
		pid = minishell->pids[minishell->count_pipee];
		minishell->count_pipee--;
	}
	pidvalue = wait(&statuetemp);
	while (pidvalue > 0)
	{
		if (coredumped == 0 && check_sig(statuetemp) == 1)
			coredumped = 1;
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

void	ft_no_perm_child(t_minishell *minishell, t_pipe *exec, int i)
{
	int	pid;

	pid = fork();
	minishell->pids[i] = pid;
	if (pid == 0)
	{
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish_child(minishell, exec, 1);
	}
}

void	ft_loop_pipe(t_minishell *minishell, t_pipe *exec, int i)
{
	while (++i <= minishell->count_pipee)
	{
		if (check_perm(exec, minishell, i) == 0)
		{
			if (check_builtins(minishell, i) == 1)
			{
				if (i == 0)
					execve_builtin_first(minishell, exec);
				else
					execve_builtin_next(minishell, exec, i, 1);
			}
			else if (i == 0)
				execve_first(minishell, exec);
			else if (i > 0)
				execve_next(minishell, exec, i, 1);
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
	t_pipe	exec;
	int		status;

	status = 0;
	init_exec(&exec, minishell->env);
	if (check_builtins(minishell, 0) != 0 && minishell->count_pipee == 0)
	{
		status = message_error_output(minishell, &exec,
				(execve_builtin_no_child(minishell, &exec, 0, 0)),
				minishell->pipex->cmd[0]);
		return (status);
	}
	minishell->pids = ft_calloc(minishell->count_pipee + 1, sizeof(pid_t));
	if (minishell->pids == NULL)
		return (ft_putstr_fd("Error Malloc\n", 2));
	if (set_path_env(&exec, minishell->env) == 1)
		return (finish(&exec, minishell, 10, "Error Malloc"));
	if (pipe(exec.pipe) == -1)
		return (finish(&exec, minishell, status, "Error pipe"));
	ft_loop_pipe(minishell, &exec, -1);
	wait_child(minishell, 0, 0, 0);
	status = minishell->return_command;
	finish(&exec, minishell, status, NULL);
	return (0);
}
