/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:22:59 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "use_free.h"

int	if_is_only_space_or_point(t_minishell *minishell)
{
	if (is_only_space_or_point(minishell->pipex[0].cmd[0]) == 1)
	{
		if (minishell->pipex[0].cmd[0][0] == '.'
			&& minishell->pipex[0].cmd[0][1] == '\0')
			return (2);
		return (127);
	}
	return (0);
}

static int	run_execve_next(t_minishell *minishell, t_pipe *exec, int *new_pipe,
		int i)
{
	ft_close(&exec->pipe[1]);
	if (close_and_dup_last(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		if (if_is_only_space_or_point(minishell) == 127)
			return (127);
		if (if_is_only_space_or_point(minishell) == 2)
			return (2);
		if (ft_strchr(minishell->pipex[i].cmd[0], '/') != NULL)
		{
			if (access(minishell->pipex[i].cmd[0], F_OK) == 0)
			{
				execve(minishell->pipex[i].cmd[0], minishell->pipex[i].cmd,
					exec->env);
				return (126);
			}
			else
				return (127);
		}
		else
			return (exec_to_env(minishell, exec, 0, i));
	}
	else
		return (0);
}

int	execve_next(t_minishell *minishell, t_pipe *exec, int i, int return_exec)
{
	pid_t	pid;
	int		new_pipe[2];

	if (pipe(new_pipe) < 0)
		error_fork_or_pipe(exec, minishell, NULL, 1);
	pid = fork();
	minishell->pids[i] = pid;
	if (pid == -1)
		error_fork_or_pipe(exec, minishell, new_pipe, 0);
	if (pid == 0)
	{
		setup_signals_child();
		if (exec->error == 0)
			return_exec = run_execve_next(minishell, exec, new_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		close_pip(exec, new_pipe, 0);
		if (exec->fd_outfile.type != t_pipeE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish_child(minishell, exec, return_exec);
	}
	else
		close_pip(exec, new_pipe, 1);
	return (0);
}
