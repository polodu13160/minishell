/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm_infiles_outfiles_in_child.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:22:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/06 22:26:47 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
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

int	check_perm_infiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	while (minishell->pipex[i].infiles[++j].value != NULL
		&& minishell->pipex[i].infiles[j].type != T_IGNORE)
	{
		if (minishell->pipex[i].infiles[j].type == T_AMBIGOUS)
			return (perr_exec_error(minishell->pipex[i].infiles[j].value, exec,
					1));
		if (minishell->pipex[i].infiles[j].type != T_HEREDOC
			&& minishell->pipex[i].infiles[j].type != T_PIPE
			&& access(minishell->pipex[i].infiles[j].value, R_OK) == -1)
			return (perr_exec_error(minishell->pipex[i].infiles[j].value, exec,
					0));
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
						exec, 0));
		}
	}
	j = -1;
	ft_close_here_doc(i, minishell, exec, 0);
	return (0);
}

int	check_perm_outfiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	while (minishell->pipex[i].outfiles[++j].value != NULL
		&& minishell->pipex[i].outfiles[j].type != T_IGNORE)
	{
		if (minishell->pipex[i].outfiles[j].type != T_PIPE)
		{
			if (check_acces_outfiles(minishell, i, j, exec) == 1)
			{
				ft_close(&exec->fd_infile.fd);
				return (1);
			}
		}
	}
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

int	count_tokens_error_files_and_ignore(t_token *tokens, int type, int error,
		int i)
{
	while (tokens[++i].value != NULL)
	{
		if (error > -1)
			tokens[i].type = T_IGNORE;
		if (type == T_REDIRECT_IN)
		{
			if ((tokens[i].type == T_AMBIGOUS) || (tokens[i].type != T_HEREDOC
					&& tokens[i].type != T_PIPE && access(tokens[i].value,
						R_OK) == -1))
				if (error == -1)
					error = tokens[i].index;
		}
		else if (type == T_REDIRECT_OUT)
		{
			if ((tokens[i].type == T_AMBIGOUS) || (access(tokens[i].value,
						F_OK) == 0 && access(tokens[i].value, W_OK) == -1))
				if (error == -1)
					error = tokens[i].index;
		}
	}
	return (error);
}

int	check_perm(t_pip *exec, t_minishell *minishell, int i)
{
	int	j;
	int	index_error_infiles;
	int	index_error_outfiles;
	int	error;

	error = 0;
	init_exec_loop(exec);
	index_error_infiles = count_tokens_error_files_and_ignore(minishell->pipex[i].infiles,
			T_REDIRECT_IN, -1, -1);
	index_error_outfiles = count_tokens_error_files_and_ignore(minishell->pipex[i].outfiles,
			T_REDIRECT_OUT, -1, -1);
	j = -1;
	if (index_error_outfiles != -1)
	{
		while (minishell->pipex[i].infiles[++j].value)
			if (minishell->pipex[i].infiles[j].index > index_error_outfiles)
				minishell->pipex[i].infiles[j].type = T_IGNORE;
	}
	j = -1;
	if (index_error_infiles != -1)
	{
		while (minishell->pipex[i].outfiles[++j].value)
			if (minishell->pipex[i].outfiles[j].index > index_error_infiles)
				minishell->pipex[i].outfiles[j].type = T_IGNORE;
	}
	if (check_perm_infiles(minishell, i, -1, exec) == 1)
		error = 1;
	if (check_perm_outfiles(minishell, i, -1, exec) == 1)
		error = 1;
	return (error);
}
