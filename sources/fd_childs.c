/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:22:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/05 18:18:38 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	check_perm_infiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	while (minishell->pipex[i].infiles[++j].value != NULL)
	{
		if (minishell->pipex[i].infiles[j].type != T_PIPE
			&& access(minishell->pipex[i].infiles[j].value, R_OK) == -1)
		{
			return (perr_and_rplce_exec_error(minishell->pipex[i].\
				infiles[j].value, exec));
		}
	}
	if (j > 0)
	{
		exec->fd_infile = minishell->pipex[i].infiles[--j];
		if (minishell->pipex[i].infiles[j].type != T_PIPE)
		{
			exec->fd_infile.fd = open(minishell->pipex[i].infiles[j].value,
					O_RDONLY);
			if (exec->fd_infile.fd == -1)
				return (perr_and_rplce_exec_error(minishell->pipex[i].\
				infiles[j].value, exec));
		}
	}
	return (0);
}

int	check_perm_outfiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	if (j > 0)
	{
		if (minishell->pipex[i].outfiles[--j].type == T_PIPE)
		{
			if (j >= 1)
				j--;
		}
		exec->fd_outfile = minishell->pipex[i].outfiles[j];
		if (minishell->pipex[i].outfiles[j].type == T_APPEND)
			exec->fd_outfile.fd = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (minishell->pipex[i].outfiles[j].type != T_PIPE)
		{
			exec->fd_outfile.fd = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (exec->fd_outfile.fd == -1)
			{
				perror(minishell->pipex[i].outfiles[j].value);
				exec->error = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	ft_check_perm(t_pip *exec, t_minishell *minishell, int i)
{
	int	j;

	init_exec_loop(exec);
	j = -1;
	if (check_perm_infiles(minishell, i, j, exec) == -1)
		return (1);
	while (minishell->pipex[i].outfiles[++j].value != NULL)
		;
	if (check_perm_outfiles(minishell, i, j, exec) == 1)
		return (1);
	return (0);
}

int	ft_close_and_dup(t_pip *exec)
{
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
		return (8);
	if (dup2(exec->fd_outfile.fd, 1) == -1)
		return (8);
	if (exec->fd_infile.fd != 0)
		ft_close(&exec->fd_infile.fd);
	if (exec->fd_outfile.fd != 1)
		ft_close(&exec->fd_outfile.fd);
	return (0);
}

int	ft_close_and_dup_finish(t_pip *exec, int *new_pipe)
{
	ft_close(&exec->pipe[1]);
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
		return (8);
	if (dup2(exec->fd_outfile.fd, 1) == -1)
		return (8);
	if (exec->fd_outfile.fd != 1)
		ft_close(&exec->fd_outfile.fd);
	if (exec->fd_infile.fd != 0)
		ft_close(&exec->fd_infile.fd);
	ft_close(&new_pipe[0]);
	if (exec->fd_outfile.type != T_PIPE)
		ft_close(&new_pipe[1]);
	return (0);
}
