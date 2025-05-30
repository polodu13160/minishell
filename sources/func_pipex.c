/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:09:40 by pde-petr          #+#    #+#             */
/*   Updated: 2025/05/30 23:24:10 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_add_slash_to_env(t_pip *exec)
{
	char	*new_path;
	int		i;

	i = 0;
	while (exec->path_args[i])
		i++;
	while (--i >= 0)
	{
		new_path = ft_strjoin(exec->path_args[i], "/");
		if (new_path == NULL)
			return (1);
		free(exec->path_args[i]);
		exec->path_args[i] = new_path;
	}
	return (0);
}

int	ft_set_path_env(t_pip *exec, char **env)
{
	char	*text;

	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			text = ft_memchr(*env, '=', 5);
			text++;
			if (text == 0)
			{
				ft_printf("No path env");
				return (1);
			}
			exec->path_args = ft_split(text, ':');
			if (exec->path_args == NULL || ft_add_slash_to_env(exec) == 1)
			{
				ft_printf("Error Malloc");
				return (1);
			}
			break ;
		}
		env++;
	}
	return (0);
}

int	ft_check_perm(t_pip *exec, t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (minishell->pipex[i].infiles[j].value != NULL)
	{
		if (minishell->pipex[i].infiles[j].type != T_PIPE
			&& access(minishell->pipex[i].infiles[j].value, R_OK) == -1)
		{
			perror(minishell->pipex[i].infiles[j].value);
			exec->error = 1;
			return (1);
		}
		j++;
	}
	if (j > 0)
	{
		exec->fd_infile = minishell->pipex[i].infiles[--j];
		if (minishell->pipex[i].infiles[j].type != T_PIPE)
			exec->fd_infile.fd[0] = open(minishell->pipex[i].infiles[j].value,
					O_RDONLY);
		if (exec->fd_infile.fd[0] == -1)
		{
			perror(minishell->pipex[i].infiles->value);
			exec->error = 1;
			return (1);
		}
	}
	j = 0;
	while (minishell->pipex[i].outfiles[j].value != NULL)
		j++;
	if (j > 0)
	{
		if (minishell->pipex[i].outfiles[j].type == T_PIPE)
		{
			if (j > 1)
				j--;
		}
		exec->fd_outfile = minishell->pipex[i].outfiles[--j];
		if (minishell->pipex[i].outfiles[j].type == T_APPEND)
			exec->fd_outfile.fd[1] = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (minishell->pipex[i].outfiles[j].type != T_PIPE)
		{
			exec->fd_outfile.fd[1] = open(minishell->pipex[i].outfiles[j].value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		if (exec->fd_outfile.fd[1] == -1)
		{
			perror(minishell->pipex[i].outfiles[j].value);
			exec->error = 1;
			return (1);
		}
	}
	return (0);
}

void	ft_check_no_pipe(t_minishell *minishell, t_pip *exec)
{
	if (exec->fd_infile.value == NULL)
		exec->fd_infile.fd[0] = 0;
	else if (exec->fd_infile.type == T_PIPE)
		close(exec->fd_infile.fd[1]);
	if (exec->fd_outfile.value == NULL)
	{
		
		exec->fd_outfile.fd[1] = 1;
	}
		
	else if (exec->fd_outfile.type == T_PIPE)
		close(exec->fd_outfile.fd[0]);
	if (dup2(exec->fd_infile.fd[0], 0) == -1 || dup2(exec->fd_outfile.fd[1],
			1) == -1)
	{
		if (exec->fd_infile.type == T_PIPE)
		{
			close(exec->fd_infile.fd[0]);
			close(exec->fd_infile.fd[1]);
		}
		else
			close(exec->fd_infile.fd[0]);
		if (exec->fd_outfile.type == T_PIPE)
		{
			close(exec->fd_outfile.fd[0]);
			close(exec->fd_outfile.fd[1]);
		}
		else
			close(exec->fd_outfile.fd[1]);
		perror("Error dup");
		free_error(minishell->tokens, minishell, 0);
		exit(1);
	}
	if (exec->fd_infile.fd[0] != 0)
		close(exec->fd_infile.fd[0]);
	if (exec->fd_outfile.fd[1] != 1)
		close(exec->fd_outfile.fd[1]);
}

void	ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i, int arg_exec)
{
	int	test_acces;

	while (exec->path_args[i])
	{
		exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
				minishell->pipex[arg_exec].cmd[0]);
		if (exec->path_absolut_exec == NULL)
		{
			free_error(minishell->tokens, minishell, 0);
			exit(-1);
		}
		test_acces = access(exec->path_absolut_exec, F_OK);
		if (test_acces == 0)
		{
			execve(exec->path_absolut_exec, minishell->pipex[arg_exec].cmd,
				exec->env);
			free_error(minishell->tokens, minishell, 0);
			exit(126);
		}
		free(exec->path_absolut_exec);
		exec->path_absolut_exec = NULL;
		i++;
	}
}

static void	ft_execve_first_child(t_minishell *minishell, t_pip *exec, int i)
{
	int	test_acces;

	// close(fd[0]);
	ft_check_no_pipe(minishell, exec);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		test_acces = access(minishell->pipex[i].cmd[0], F_OK);
		if (test_acces == 0 && ft_strchr(minishell->pipex[i].cmd[0], '/') != 0)
		{
			execve(minishell->pipex[i].cmd[0], minishell->pipex[i].cmd,
				exec->env);
			exit(126);
		}
		else
			ft_exec_to_env(minishell, exec, 0, i);
	}
	free_error(minishell->tokens, minishell, 0);
	exit(127);
}

int	ft_exec(t_minishell *minishell, t_pip *exec, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	minishell->pids[i] = pid;
	if (pid == 0)
	{
		if (exec->error != 1)
		{
			if (pid == 0)
			{
				ft_execve_first_child(minishell, exec, i);
				if (exec->fd_infile.type == T_PIPE)
				{
					close(exec->fd_infile.fd[0]);
					close(exec->fd_infile.fd[1]);
				}
				else
					close(exec->fd_infile.fd[0]);
				if (exec->fd_outfile.type == T_PIPE)
				{
					close(exec->fd_outfile.fd[0]);
					close(exec->fd_outfile.fd[1]);
				}
				else
					close(exec->fd_outfile.fd[1]);
				free_error(minishell->tokens, minishell, 0);
				exit(126);
			}
		}
		else
		{
			if (exec->fd_infile.type == T_PIPE)
			{
				close(exec->fd_infile.fd[0]);
				close(exec->fd_infile.fd[1]);
			}
			else
				close(exec->fd_infile.fd[0]);
			if (exec->fd_outfile.type == T_PIPE)
			{
				close(exec->fd_outfile.fd[0]);
				close(exec->fd_outfile.fd[1]);
			}
			else
				close(exec->fd_outfile.fd[1]);
			free_error(minishell->tokens, minishell, 0);
			exit(1);
		}
	}
	close(exec->fd_infile.fd[0]);
	close(exec->fd_outfile.fd[1]);
	return (0);
}
