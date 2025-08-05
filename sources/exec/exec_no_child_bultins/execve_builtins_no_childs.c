/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins_no_childs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:06:15 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 19:47:03 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "unistd.h"
#include <libft.h>

static int	continue_if_no_exit(t_minishell *minishell, t_pip *exec,
		int dup_redirect_in, int dup_redirect_out)
{
	if (ft_strcmp(minishell->pipex[0].cmd[0], "exit") != 0)
	{
		if (dup2(dup_redirect_in, 0) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		if (dup2(dup_redirect_out, 1) == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		close_2_fds(&dup_redirect_in, &dup_redirect_out);
	}
	return (0);
}

int	error_dup2_execve_builtin_no_child(t_pip *exec, int dup_redirect_in,
		int dup_redirect_out)
{
	ft_close(&dup_redirect_in);
	ft_close(&dup_redirect_out);
	ft_close(&exec->fd_infile.fd);
	ft_close(&exec->fd_outfile.fd);
	return (8);
}

int	execve_builtin_no_child(t_minishell *minishell, t_pip *exec,
		int dup_redirect_in, int dup_redirect_out)
{
	if (check_perm(exec, minishell, 0) == 0)
	{
		dup_redirect_in = dup(0);
		dup_redirect_out = dup(1);
		if (dup_redirect_in == -1 || dup_redirect_out == -1)
			return (error_dup2_execve_builtin_no_child(exec, dup_redirect_in,
					dup_redirect_out));
		if (ft_strcmp(minishell->pipex[0].cmd[0], "exit") == 0)
		{
			close_2_fds(&dup_redirect_in, &dup_redirect_out);
			close_2_fds(&exec->fd_infile.fd, &exec->fd_outfile.fd);
		}
		else if (dup_infile_and_outfile_builtin_no_child(exec, dup_redirect_in,
				dup_redirect_out) == 8)
			return (8);
		minishell->return_command = apply_builtins(minishell, 0, exec, 1);
		if (continue_if_no_exit(minishell, exec, dup_redirect_in,
				dup_redirect_out) == 8)
			return (8);
		return (minishell->return_command);
	}
	return (1);
}
