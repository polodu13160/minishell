/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:09:53 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/16 17:50:25 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"

void	ft_free_exec(t_pip *exec)
{
	int	i;

	if (exec)
	{
		if (exec->path_absolut_exec)
			free(exec->path_absolut_exec);
		if (exec->path_args)
		{
			i = 0;
			while (exec->path_args[i])
			{
				free(exec->path_args[i]);
				i++;
			}
			free(exec->path_args);
		}
	}
}

void	ft_free_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			free(minishell->env[i]);
			i++;
		}
		free(minishell->env);
	}
}

void	ft_free_tokens(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->tokens)
	{
		while (minishell->tokens[i].type != T_NULL)
		{
			if (minishell->tokens[i].value)
				free(minishell->tokens[i].value);
			i++;
		}
		free(minishell->tokens);
	}
}

void	free_pipex(t_minishell *minishell, int end)
{
	int	i;

	i = 0;
	if (minishell->pipex)
	{
		while (minishell->pipex[i].init != 1)
		{
			if (minishell->pipex[i].cmd != NULL)
				free(minishell->pipex[i].cmd);
			minishell->pipex[i].cmd = NULL;
			if (minishell->pipex[i].infiles != NULL)
				free(minishell->pipex[i].infiles);
			minishell->pipex[i].infiles = NULL;
			if (minishell->pipex[i].outfiles != NULL)
				free(minishell->pipex[i].outfiles);
			minishell->pipex[i++].outfiles = NULL;
		}
		free(minishell->pipex);
		minishell->pipex = NULL;
	}
	if (minishell->pids != NULL)
		free(minishell->pids);
	minishell->pids = NULL;
	if (end > 0)
		exit(minishell->return_command);
}

void	ft_finish_child(t_minishell *minishell, t_pip *exec, int exit_return)
{
	ft_free_exec(exec);
	ft_free_env(minishell);
	ft_free_tokens(minishell);
	free_pipex(minishell, 0);
	free(minishell->line);
	if (minishell->cwd)
		free(minishell->cwd);
	if (minishell->cwd_join)
		free(minishell->cwd_join);
	exit(exit_return);
}
