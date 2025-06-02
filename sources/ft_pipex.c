/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/02 17:04:48 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include <stdio.h>
#include <sys/wait.h>

void	*ft_error_free_tab(t_token *tab)
{
	int	i;

	i = 0;
	free(tab);
	return (NULL);
}
t_token	*ft_check_outfiles(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_outfiles;
	int		j;
	t_token	*malloc_outfiles;

	count_pipe = 0;
	i = 0;
	count_outfiles = 0;
	malloc_outfiles = NULL;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == var_count_pipe + 1)
				count_outfiles++;
		}
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				count_outfiles++;
		i++;
	}
	count_pipe = 0;
	malloc_outfiles = ft_calloc(count_outfiles + 1, sizeof(t_token));
	if (malloc_outfiles == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == var_count_pipe + 1)
				malloc_outfiles[j++] = tokens[i];
		}
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
			{
				free(tokens[i].value);
				tokens[i].value = ft_strdup(tokens[i + 1].value);
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_outfiles[j++] = tokens[i];
			}
		i++;
	}
	malloc_outfiles[j].value = NULL;
	return (malloc_outfiles);
}

t_token	*ft_check_infiles(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_infiles;
	int		j;
	t_token	*malloc_infiles;

	count_pipe = 0;
	i = 0;
	count_infiles = 0;
	malloc_infiles = NULL;
	while (tokens[i].value)
	{
		tokens[i].fd = -1;
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == var_count_pipe)
				count_infiles++;
		}
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
				count_infiles++;
		i++;
	}
	count_pipe = 0;
	malloc_infiles = ft_calloc(count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			count_pipe++;
			if (count_pipe == var_count_pipe)
				malloc_infiles[j++] = tokens[i];
		}
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
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
		i++;
	}
	malloc_infiles[j].value = NULL;
	return (malloc_infiles);
}

char	**ft_check_cmd(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_cmd;
	int		j;
	char	**malloc_cmd;

	count_pipe = 0;
	i = 0;
	count_cmd = 0;
	malloc_cmd = NULL;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
				count_cmd++;
		i++;
	}
	count_pipe = 0;
	malloc_cmd = ft_calloc(count_cmd + 1, sizeof(char *));
	if (malloc_cmd == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
			{
				malloc_cmd[j++] = tokens[i].value;
			}
		i++;
	}
	malloc_cmd[j] = NULL;
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

int	ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens)
{
	int	var_count_pipe;
	int	i;
	int	j;

	var_count_pipe = 0;
	minishell->count_pipe = count_pipe(tokens);
	minishell->pipex = ft_calloc(minishell->count_pipe + 2, sizeof(t_pipex));
	while (var_count_pipe <= count_pipe(tokens))
	{
		minishell->pipex[var_count_pipe].infiles = ft_check_infiles(tokens,
				var_count_pipe);
		minishell->pipex[var_count_pipe].outfiles = ft_check_outfiles(tokens,
				var_count_pipe);
		minishell->pipex[var_count_pipe].cmd = ft_check_cmd(tokens,
				var_count_pipe);
		if (minishell->pipex[var_count_pipe].infiles == NULL
			|| minishell->pipex[var_count_pipe].outfiles == NULL
			|| minishell->pipex[var_count_pipe].cmd == NULL)
		{
			free(minishell->pipex[var_count_pipe].outfiles);
			free(minishell->pipex[var_count_pipe].infiles);
			free(minishell->pipex[var_count_pipe].cmd);
			return (1);
		}
		minishell->pipex[var_count_pipe].init = 0;
		var_count_pipe++;
	}
	minishell->pipex[var_count_pipe].init = 1;
	i = 0;
	j = 0;
	// free tout ca
	while (minishell->pipex[j].init != 1)
	{
		printf("pipe n  %d\n", j);
		i = 0;
		while (minishell->pipex[j].infiles[i].value != NULL)
		{
			printf("infile %s\n", minishell->pipex[j].infiles[i].value);
			i++;
		}
		i = 0;
		while (minishell->pipex[j].cmd[i] != NULL)
		{
			printf("cmd %s\n", minishell->pipex[j].cmd[i]);
			i++;
		}
		i = 0;
		while (minishell->pipex[j].outfiles[i].value != NULL)
		{
			printf("outfile %s\n", minishell->pipex[j].outfiles[i].value);
			i++;
		}
		// i = 0;
		// while(minishell->pipex[j].cmd[i] != NULL)
		// {
		// 	printf("cmd %s\n" ,minishell->pipex[j].cmd[i]);
		// 	i++;
		// }
		// free(minishell->pipex[j].outfiles);
		// free(minishell->pipex[j].infiles);
		// free(minishell->pipex[j].cmd);
		j++;
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

void	finish(t_pip exec, t_minishell *minishell, int full)
{
	int	i;

	i = 0;
	if (exec.path_args != NULL)
	{
		while (exec.path_args[i])
			free(exec.path_args[i++]);
		free(exec.path_args);
	}
	if (full == 1)
		free_error(minishell->tokens, minishell, 0);
}

int	ft_pipex(t_minishell *minishell)
{
	t_pip exec;
	init_exec(&exec, minishell->env);
	int i;
	int status;
	i = 0;
	minishell->pids = ft_calloc(minishell->count_pipe + 1, sizeof(pid_t));

	if (minishell->pids == NULL)
	{
		// finish(&exec);
		// free_error(minishell->tokens, minishell, 0);
		ft_putstr_fd("Error Malloc", 2);
		return (1);
	}
	if (ft_set_path_env(&exec, minishell->env) == 1)
		return (1);
	if (pipe(exec.pipe) == -1)
		return (1);
	while (i <= minishell->count_pipe)
	{
		
		if (ft_check_perm(&exec, minishell, i) == 0)
		{
			if (i == 0)
			{
				ft_execve_first(minishell, &exec);
				
			}
			
			if (i > 0)
				break;
		}
		i++;
	}
	status = WEXITSTATUS(ft_wait_child(minishell));
	minishell->return_command = status;
	printf("DEBUG: Final return_command = %d\n", minishell->return_command);

	finish(exec, minishell, 0);
	// free_error(minishell->tokens,minishell, 0);
	return (0);
}