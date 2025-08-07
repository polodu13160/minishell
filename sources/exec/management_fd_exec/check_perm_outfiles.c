/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm_outfiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:22:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 22:46:29 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

int	check_acces_outfiles(t_minishell *minishell, int i, int j, t_pip *exec)
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

int	while_perm_outfiles(int *j, t_minishell *minishell, int i, t_pip *exec)
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

int	check_perm_outfiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	if (while_perm_outfiles(&j, minishell, i, exec) == 1)
		return (1);
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
			exec->fd_outfile.fd = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (minishell->pipex[i].outfiles[j].type != T_PIPE
			&& exec->fd_outfile.fd == -1)
		{
			ft_close(&exec->fd_infile.fd);
			return (perr_exec_error\
(minishell->pipex[i].outfiles[j].value, exec, 0));
		}
	}
	return (0);
}
