/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:09:53 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 21:11:57 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"


void	free_pipex(t_minishell *structure, int end)
{
	int	i;

	i = 0;
	if (structure->pipex)
	{
		while (structure->pipex[i].init != 1)
		{
			if (structure->pipex[i].cmd != NULL)
				free(structure->pipex[i].cmd);
			if (structure->pipex[i].infiles != NULL)
				free(structure->pipex[i].infiles);
			if (structure->pipex[i].outfiles != NULL)
				free(structure->pipex[i].outfiles);
			i++;
		}
		free(structure->pipex);
	}
	if (structure->pids != NULL)
		free(structure->pids);
	if (end > 0)
	{
		exit(structure->code_error);
	}
}

int	free_error(t_token *token, t_minishell *structure, int end)
{
	int	i;

	if (end == 2)
		perror("Malloc error ");
	i = 0;
	if (token)
	{
		while (token[i].value)
			free(token[i++].value);
		free(token);
	}
	i = 0;
	free(structure->line);
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	free_pipex(structure, end);
	return (0);
}

void	free_loop(t_token *token, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i].value)
		{
			free(token[i].value);
			i++;
		}
		free(token);
	}
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

void	free_exit(t_token *token, t_minishell *minishell, t_pip *exec)
{
	free_loop(token, minishell);
	if (exec)
	finish(exec, minishell, 2);
	// free_pipex(minishell, 0);
	if (minishell->cwd)
		free(minishell->cwd);
	if (minishell->cwd_join)
		free(minishell->cwd_join);
	if (minishell->line)
		free(minishell->line);
	exit(minishell->code_error);
}
