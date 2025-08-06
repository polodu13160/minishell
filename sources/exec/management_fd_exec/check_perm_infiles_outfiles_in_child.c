/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm_infiles_outfiles_in_child.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:22:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/06 16:04:51 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "token.h"

int	check_acces_outfiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	int	fd;

	if (access(minishell->pipex[i].outfiles[j].value, F_OK) == 0
		&& access(minishell->pipex[i].outfiles[j].value, W_OK) == -1)
		return (perr_exec_error(minishell->pipex[i].outfiles[j].value, exec));
	else
	{
		fd = open(minishell->pipex[i].outfiles[j].value,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			return (perr_exec_error(minishell->pipex[i].outfiles[j].value,
					exec));
		}
		ft_close(&fd);
	}
	return (0);
}

int	check_perm_infiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	while (minishell->pipex[i].infiles[++j].value != NULL)
	{
		if (minishell->pipex[i].infiles[j].type != T_HEREDOC
			&& minishell->pipex[i].infiles[j].type != T_PIPE
			&& access(minishell->pipex[i].infiles[j].value, R_OK) == -1)
			return (perr_exec_error(minishell->pipex[i].infiles[j].value,
					exec));
	}
	if (j > 0)
	{
		exec->fd_infile = minishell->pipex[i].infiles[--j];
		if (minishell->pipex[i].infiles[j].type != T_PIPE)
		{
			if (exec->fd_infile.type != T_HEREDOC)
				exec->fd_infile.fd = open(minishell->pipex[i].infiles[j].value,
						O_RDONLY);
			if (exec->fd_infile.fd == -1)
				return (perr_exec_error(minishell->pipex[i].infiles[j].value,
						exec));
		}
	}
	j = -1;
	ft_close_here_doc(i, minishell, exec, 0);
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
			exec->fd_outfile.fd = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (minishell->pipex[i].outfiles[j].type != T_PIPE
			&& exec->fd_outfile.fd == -1)
		{
			ft_close(&exec->fd_infile.fd);
			perror(minishell->pipex[i].outfiles[j].value);
			exec->error = 1;
			return (1);
		}
	}
	return (0);
}

int	check_perm(t_pip *exec, t_minishell *minishell, int i)
{
	int	j;

	init_exec_loop(exec);
	j = -1;
	if (check_perm_infiles(minishell, i, j, exec) == 1)
		return (1);
	j = -1;
	
	
	



	// while (minishell->pipex[i].outfiles[++j].value != NULL)
	// {
	// 	if (minishell->pipex[i].outfiles[j].type != T_PIPE)
	// 	{
	// 		if (check_acces_outfiles(minishell, i, j, exec) == 1)
	// 		{
	// 			ft_close(&exec->fd_infile.fd);
	// 			return (1);
	// 		}
	// 	}
	// }
	// if (check_perm_outfiles(minishell, i, j, exec) == 1)
	// 	return (1);
	return (0);
}


