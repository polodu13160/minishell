/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm_outfiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:22:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:12:12 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

int	check_acces_outfiles(t_minishell *minishell, int i, int j, t_pipe *exec)
{
	int	fd;

	if (minishell->pipex[i].outfiles[j].type == T_AMBIGOUS)
		return (perr_exec_error(minishell->pipex[i].outfiles[j].value, exec,
				1));
	if (access(minishell->pipex[i].outfiles[j].value, F_OK) == 0
		&& access(minishell->pipex[i].outfiles[j].value, W_OK) == -1)
		return (perr_exec_error(minishell->pipex[i].outfiles[j].value, exec,
				0));
	else
	{
		fd = open(minishell->pipex[i].outfiles[j].value,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			return (perr_exec_error(minishell->pipex[i].outfiles[j].value, exec,
					0));
		}
		ft_close(&fd);
	}
	return (0);
}

int	while_perm_outfiles(int *j, t_minishell *minishell, int i, t_pipe *exec)
{
	while (minishell->pipex[i].outfiles[++*j].value != NULL
		&& minishell->pipex[i].outfiles[*j].type != T_IGNORE)
	{
		if (minishell->pipex[i].outfiles[*j].type != T_PIPE)
		{
			if (check_acces_outfiles(minishell, i, *j, exec) == 1)
			{
				ft_close(&exec->fd_infile.fd);
				return (1);
			}
		}
	}
	return (0);
}

int	check_perm_outfiles(t_minishell *mshell, int i, int j, t_pipe *exec)
{
	if (while_perm_outfiles(&j, mshell, i, exec) == 1)
		return (1);
	if (j > 0)
	{
		if (mshell->pipex[i].outfiles[--j].type == T_PIPE)
		{
			if (j >= 1)
				j--;
		}
		exec->fd_outfile = mshell->pipex[i].outfiles[j];
		if (mshell->pipex[i].outfiles[j].type == T_APPEND)
			exec->fd_outfile.fd = open(mshell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		else if (mshell->pipex[i].outfiles[j].type != T_PIPE)
			exec->fd_outfile.fd = open(mshell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (mshell->pipex[i].outfiles[j].type != T_PIPE
			&& exec->fd_outfile.fd == -1)
		{
			ft_close(&exec->fd_infile.fd);
			return (perr_exec_error(mshell->pipex[i].outfiles[j].value, exec,
					0));
		}
	}
	return (0);
}
