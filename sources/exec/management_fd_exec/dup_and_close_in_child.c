/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_in_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:36:03 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/18 13:08:03 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"

int	dup_infile_and_outfile_builtin_no_child(t_pipe *exec, int dup_redirect_in,
		int dup_redirect_out)
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

int	close_and_dup(t_pipe *exec)
{
	int	return_value;

	return_value = 0;
	ft_close(&exec->pipe[0]);
	if (exec->fd_infile.value == NULL)
		exec->fd_infile.fd = 0;
	if (exec->fd_outfile.value == NULL)
		exec->fd_outfile.fd = 1;
	if (exec->fd_outfile.type == T_PIPE)
		exec->fd_outfile.fd = exec->pipe[1];
	else
		ft_close(&exec->pipe[1]);
	if (dup2(exec->fd_infile.fd, 0) == -1)
		return_value = 8;
	if (dup2(exec->fd_outfile.fd, 1) == -1)
		return_value = 8;
	if (exec->fd_infile.fd != 0)
		ft_close(&exec->fd_infile.fd);
	if (exec->fd_outfile.fd != 1)
		ft_close(&exec->fd_outfile.fd);
	return (return_value);
}

int	close_and_dup_last(t_pipe *exec, int *new_pipe)
{
	int	return_value;

	return_value = 0;
	if (exec->fd_outfile.value == NULL)
		exec->fd_outfile.fd = 1;
	if (exec->fd_infile.type == T_PIPE)
		exec->fd_infile.fd = exec->pipe[0];
	else
		ft_close(&exec->pipe[0]);
	if (exec->fd_outfile.type == T_PIPE)
		exec->fd_outfile.fd = new_pipe[1];
	else
		ft_close(&exec->pipe[1]);
	if (dup2(exec->fd_infile.fd, 0) == -1)
		return_value = 8;
	if (dup2(exec->fd_outfile.fd, 1) == -1)
		return_value = 8;
	if (exec->fd_outfile.fd != 1)
		ft_close(&exec->fd_outfile.fd);
	if (exec->fd_infile.fd != 0)
		ft_close(&exec->fd_infile.fd);
	ft_close(&new_pipe[0]);
	if (exec->fd_outfile.type != T_PIPE)
		ft_close(&new_pipe[1]);
	return (return_value);
}
