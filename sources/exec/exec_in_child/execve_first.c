/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:21:59 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 19:27:53 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipex.h"
#include "unistd.h"
#include "use_free.h"
#include "libft.h"

int	is_only_space_or_point(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str != 32 && (*str < 9 || *str > 13) && *str != '.')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

static int	ft_execve_first_child(t_minishell *minishell, t_pip *exec)
{
	if (close_and_dup(exec) == 8)
		return (8);
	if (minishell->pipex[0].cmd[0] != NULL)
	{
		if (is_only_space_or_point(minishell->pipex[0].cmd[0]) == 1)
			return (127);
		if (ft_strchr(minishell->pipex[0].cmd[0], '/') != NULL)
		{
			if (access(minishell->pipex[0].cmd[0], F_OK) == 0)
			{
				execve(minishell->pipex[0].cmd[0], minishell->pipex[0].cmd,
					exec->env);
				return (126);
			}
			else
				return (127);
		}
		else
			return (exec_to_env(minishell, exec, 0, 0));
	}
	else
		return (0);
	return (127);
}

int	execve_first(t_minishell *minishell, t_pip *exec)
{
	pid_t pid;
	int return_exec;

	pid = fork();
	return_exec = 1;
	minishell->pids[0] = pid;
	if (pid == -1)
		error_fork_or_pipe(exec, minishell, NULL, 0);
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
		finish_child(minishell, exec, return_exec);
	}
	return (return_exec);
}
