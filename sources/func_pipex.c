/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:09:40 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 02:48:11 by pde-petr         ###   ########.fr       */
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

void	init_exec_loop(t_pip *exec)
{
	exec->error = 0;
	exec->fd_infile.value = NULL;
	exec->fd_infile.type = T_NULL;
	exec->fd_outfile.type = T_NULL;
	exec->fd_outfile.value = NULL;
	exec->fd_infile.fd = -1;
	exec->fd_outfile.fd = -1;
}

int	perror_and_replace_exec_error(char *value, t_pip *exec)
{
	perror(value);
	exec->error = 1;
	return (1);
}

int	check_perm_infiles(t_minishell *minishell, int i, int j, t_pip *exec)
{
	while (minishell->pipex[i].infiles[++j].value != NULL)
	{
		if (minishell->pipex[i].infiles[j].type != T_PIPE
			&& access(minishell->pipex[i].infiles[j].value, R_OK) == -1)
			return (perror_and_replace_exec_error(minishell->pipex[i].infiles[j].value,
					exec));
	}
	if (j > 0)
	{
		exec->fd_infile = minishell->pipex[i].infiles[--j];
		if (minishell->pipex[i].infiles[j].type != T_PIPE)
		{
			exec->fd_infile.fd = open(minishell->pipex[i].infiles[j].value,
					O_RDONLY);
			if (exec->fd_infile.fd == -1)
				return (perror_and_replace_exec_error(minishell->pipex[i].infiles[j].value,
						exec));
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

static int	ft_close_and_dup(t_pip *exec)
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

static int	ft_execve_first_child(t_minishell *minishell, t_pip *exec)
{
	int	test_acces;

	if (ft_close_and_dup(exec) == 8)
		return (8);
	if (minishell->pipex[0].cmd[0] != NULL)
	{
		test_acces = access(minishell->pipex[0].cmd[0], F_OK);
		if (test_acces == 0 && ft_strchr(minishell->pipex[0].cmd[0], '/') != 0)
		{
			execve(minishell->pipex[0].cmd[0], minishell->pipex[0].cmd,
				exec->env);
			return (126);
		}
		else
			ft_exec_to_env(minishell, exec, 0, 0);
	}
	return (127);
}

static int	ft_close_and_dup_finish(t_pip *exec, int *new_pipe)
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

static int	ft_execve_finish(t_minishell *minishell, t_pip *exec, int *new_pipe,
		int i)
{
	int	test_acces;

	if (ft_close_and_dup_finish(exec, new_pipe) == 8)
		return (8);
	if (minishell->pipex[i].cmd[0] != NULL)
	{
		test_acces = access(minishell->pipex[i].cmd[0], F_OK);
		if (test_acces == 0 && ft_strchr(minishell->pipex[i].cmd[0], '/') != 0)
		{
			execve(minishell->pipex[i].cmd[0], minishell->pipex[i].cmd,
				exec->env);
			return (126);
		}
		else
			ft_exec_to_env(minishell, exec, 0, i);
	}
	return (127);
}

void	ft_close_pip(t_pip *exec, int *new_pipe, int substitue)
{
	ft_close(&exec->pipe[0]);
	ft_close(&exec->pipe[1]);
	if (substitue == 1)
	{
		exec->pipe[0] = new_pipe[0];
		exec->pipe[1] = new_pipe[1];
	}
}

int	ft_execve_next(t_minishell *minishell, t_pip *exec, int i)
{
	pid_t	pid;
	int		new_pipe[2];
	int		return_exec;

	if (pipe(new_pipe) < 0)
		return (1);
	pid = fork();
	return_exec = 1;
	minishell->pids[i] = pid;
	if (pid == 0)
	{
		if (exec->error == 0)
			return_exec = ft_execve_finish(minishell, exec, new_pipe, i);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close_pip(exec, new_pipe, 0);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish(exec, minishell, 1);
		exit(return_exec);
	}
	else
		ft_close_pip(exec, new_pipe, 1);
	return (0);
}

int	ft_execve_first(t_minishell *minishell, t_pip *exec)
{
	pid_t	pid;
	int		return_exec;

	pid = fork();
	return_exec = 1;
	minishell->pids[0] = pid;
	if (pid == 0)
	{
		if (exec->error == 0)
			return_exec = ft_execve_first_child(minishell, exec);
		if (exec->fd_infile.value == NULL)
			ft_close(&exec->fd_infile.fd);
		ft_close(&exec->pipe[0]);
		ft_close(&exec->pipe[1]);
		if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
			ft_close(&exec->fd_outfile.fd);
		finish(exec, minishell, 1);
		exit(return_exec);
	}
	return (return_exec);
}
