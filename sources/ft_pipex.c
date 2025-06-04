/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 02:19:01 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include <stdio.h>
#include <sys/wait.h>

int	ft_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
		{
			ft_printf_fd(2, "Error closing\n");
			return (-1);
		}
		*fd = -1;
	}
	return (0);
}

void	*ft_error_free_tab(t_token *tab)
{
	int	i;

	i = 0;
	free(tab);
	return (NULL);
}

int	ft_count_outfiles(t_token *tokens, int limit_pipe)
{
	int	count_outfiles;
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	count_outfiles = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe + 1)
				count_outfiles++;
		}
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				count_outfiles++;
		i++;
	}
	return (count_outfiles);
}

int	ft_join_tab_outfiles(t_token *tokens, int limit_pipe,
		t_token *malloc_outfiles, int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe + 1)
				malloc_outfiles[j++] = tokens[i];
		}
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
			{
				free(tokens[i].value);
				tokens[i].value = ft_strdup(tokens[i + 1].value);
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_outfiles[j++] = tokens[i];
			}
	}
	return (j);
}
t_token	*ft_store_outfiles(t_token *tokens, int limit_pipe)
{
	int		count_pipe;
	int		count_outfiles;
	int		last_index_malloc_outfiles;
	t_token	*malloc_outfiles;

	count_pipe = 0;
	count_outfiles = ft_count_outfiles(tokens, limit_pipe);
	malloc_outfiles = ft_calloc(count_outfiles + 1, sizeof(t_token));
	if (malloc_outfiles == NULL)
		return (NULL);
	last_index_malloc_outfiles = ft_join_tab_outfiles(tokens, limit_pipe,
			malloc_outfiles, 0);
	malloc_outfiles[last_index_malloc_outfiles].value = NULL;
	return (malloc_outfiles);
}

int	ft_count_infiles(t_token *tokens, int limit_pipe)
{
	int	count_infiles;
	int	i;
	int	count_pipe;

	count_infiles = 0;
	i = 0;
	count_pipe = 0;
	while (tokens[i].value)
	{
		tokens[i].fd = -1;
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == limit_pipe)
				count_infiles++;
		}
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
				count_infiles++;
		i++;
	}
	return (count_infiles);
}

int	ft_join_tab_infiles(t_token *tokens, int limit_pipe,
		t_token *malloc_infiles, int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			if ((++count_pipe) == limit_pipe)
				malloc_infiles[j++] = tokens[i];
		}
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
			{
				if (tokens[i].type == T_REDIRECT_IN)
				{
					free(tokens[i].value);
					tokens[i].value = ft_strdup(tokens[i + 1].value);
				}
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_infiles[j++] = tokens[i];
			}
	}
	return (j);
}

t_token	*ft_store_infiles(t_token *tokens, int limit_pipe)
{
	int		count_infiles;
	int		last_index_malloc_infiles;
	t_token	*malloc_infiles;

	count_infiles = ft_count_infiles(tokens, limit_pipe);
	malloc_infiles = ft_calloc(count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	last_index_malloc_infiles = ft_join_tab_infiles(tokens, limit_pipe,
			malloc_infiles, 0);
	malloc_infiles[last_index_malloc_infiles].value = NULL;
	return (malloc_infiles);
}

int	ft_count_cmd(t_token *tokens, int limit_pipe)
{
	int	count_cmd;
	int	i;
	int	count_pipe;

	count_cmd = 0;
	i = 0;
	count_pipe = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				count_cmd++;
		i++;
	}
	return (count_cmd);
}
int	ft_join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
		int count_pipe)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > limit_pipe)
			break ;
		else if (count_pipe == limit_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
			{
				malloc_cmd[j++] = tokens[i].value;
			}
	}
	return (j);
}

char	**ft_store_cmd(t_token *tokens, int limit_pipe)
{
	int		count_cmd;
	int		last_index_malloc_infiles;
	char	**malloc_cmd;

	count_cmd = ft_count_cmd(tokens, limit_pipe);
	malloc_cmd = ft_calloc(count_cmd + 1, sizeof(char *));
	;
	if (malloc_cmd == NULL)
		return (NULL);
	last_index_malloc_infiles = ft_join_tab_cmd(tokens, limit_pipe, malloc_cmd,
			0);
	malloc_cmd[last_index_malloc_infiles] = NULL;
	return (malloc_cmd);
}

int	count_pipe(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == T_PIPE)
			count++;
		i++;
	}
	return (count);
}

int	init_pipex(t_minishell *minishell, int count_pipe)
{
	int	i;

	i = 0;
	minishell->pipex = ft_calloc(minishell->count_pipe + 2, sizeof(t_pipex));
	if (minishell->pipex == NULL)
		return (1);
	while (i <= count_pipe)
	{
		minishell->pipex[i].init = 0;
		minishell->pipex[i].infiles = NULL;
		minishell->pipex[i].outfiles = NULL;
		minishell->pipex[i].cmd = NULL;
		i++;
	}
	minishell->pipex[i].init = 1;
	return (0);
}

int	ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens)
{
	int	limit_pipe;

	limit_pipe = 0;
	minishell->count_pipe = count_pipe(tokens);
	if (init_pipex(minishell, minishell->count_pipe) == 1)
		return (1);
	while (limit_pipe <= count_pipe(tokens))
	{
		minishell->pipex[limit_pipe].init = 0;
		minishell->pipex[limit_pipe].infiles = ft_store_infiles(tokens,
				limit_pipe);
		minishell->pipex[limit_pipe].outfiles = ft_store_outfiles(tokens,
				limit_pipe);
		minishell->pipex[limit_pipe].cmd = ft_store_cmd(tokens, limit_pipe);
		if (minishell->pipex[limit_pipe].infiles == NULL
			|| minishell->pipex[limit_pipe].outfiles == NULL
			|| minishell->pipex[limit_pipe].cmd == NULL)
			return (1);
		limit_pipe++;
	}
	return (0);
}

void	init_exec(t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error = 0;
	exec->pipe[0] = 0;
	exec->pipe[1] = 1;
	exec->path_args = NULL;
	exec->env = env;
	exec->fd_infile.value = NULL;
	exec->fd_outfile.value = NULL;
}

int	message_error(char *first_message, char *last_message)
{
	last_message = ft_strjoin(last_message, "\n");
	if (last_message == NULL)
	{
		perror("malloc error");
		return (1);
	}
	first_message = ft_strjoin(first_message, last_message);
	if (first_message == NULL)
	{
		free(last_message);
		perror("malloc error");
		return (1);
	}
	ft_putstr_fd(first_message, 2);
	free(last_message);
	free(first_message);
	return (0);
}

void	message_output(int statuetemp, t_minishell *minishell, pid_t pidvalue)
{
	int	i;

	i = 0;
	while (pidvalue != minishell->pids[i])
		i++;
	if (WEXITSTATUS(statuetemp) != 0)
	{
		if (WEXITSTATUS(statuetemp) == 10)
			message_error("Error malloc", "in child");
		else if (WEXITSTATUS(statuetemp) == 126)
			message_error(minishell->pipex[i].cmd[0], ": Permission denied");
		else if (WEXITSTATUS(statuetemp) == 127)
		{
			if (minishell->pipex[i].cmd[0] == NULL)
				message_error("", ": Command not found");
			else
				message_error(minishell->pipex[i].cmd[0],
					": Command not found");
		}
	}
}

static int	ft_wait_child(t_minishell *minishell)
{
	int		statuetemp;
	pid_t	pidvalue;
	int		status;
	int		pid;

	status = 0;
	pid = minishell->pids[minishell->count_pipe];
	pidvalue = wait(&statuetemp);
	while (pidvalue > 0)
	{
		message_output(statuetemp, minishell, pidvalue);
		if (pidvalue == pid)
			status = statuetemp;
		pidvalue = wait(&statuetemp);
	}
	return (status);
}

void	finish(t_pip *exec, t_minishell *minishell, int full)
{
	int	i;

	i = 0;
	if (exec->path_args != NULL)
	{
		while (exec->path_args[i])
			free(exec->path_args[i++]);
		free(exec->path_args);
	}
	if (full == 1)
		free_error(minishell->tokens, minishell, 0);
}

void	ft_loop_pipe(t_minishell *minishell, t_pip *exec)
{
	int i;
	i = 0;
	while (i <= minishell->count_pipe)
	{
		if (i != 0 && exec->fd_infile.fd != -1 && exec->fd_infile.value != NULL
			&& exec->fd_infile.type != T_PIPE)
			ft_close(&exec->fd_infile.fd);
		if (ft_check_perm(exec, minishell, i) == 0)
		{
			if (i == 0)
				ft_execve_first(minishell, exec);
			if (i > 0)
				ft_execve_next(minishell, exec, i);
			if (exec->fd_infile.type != T_PIPE)
				ft_close(&exec->fd_infile.fd);
			if (exec->fd_outfile.type != T_PIPE)
				ft_close(&exec->fd_outfile.fd);
		}
		i++;
	}
}

int	ft_pipex(t_minishell *minishell)
{
	t_pip	exec;
	int		status;

	init_exec(&exec, minishell->env);
	status = 0;
	minishell->pids = ft_calloc(minishell->count_pipe + 1, sizeof(pid_t));
	if (minishell->pids == NULL)
	{
		ft_putstr_fd("Error Malloc", 2);
		return (1);
	}
	if (ft_set_path_env(&exec, minishell->env) == 1)
		return (1);
	if (pipe(exec.pipe) == -1)
		return (1);
	ft_loop_pipe(minishell,&exec);
	ft_close(&exec.pipe[0]);
	ft_close(&exec.pipe[1]);
	status = WEXITSTATUS(ft_wait_child(minishell));
	minishell->return_command = status;
	finish(&exec, minishell, 0);
	return (0);
}
