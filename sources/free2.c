/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:02:04 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/28 22:36:12 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	ft_finish(t_pip *exec, t_minishell *minishell, int status)
{
	ft_free_exec(exec);
	free_pipex(minishell, 0);
	minishell->return_command = status;
}

int	free_all(t_token *token, t_minishell *structure, int end)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i].type != T_NULL)
		{
			if (token[i].value && token[i].value != token[i + 1].value)
				free(token[i].value);
			token[i].value = NULL;
			i++;
		}
		free(token);
		token = NULL;
	}
	if (structure->line)
		free(structure->line);
	structure->line = NULL;
	if (structure->cwd_join)
		free(structure->cwd_join);
	structure->cwd_join = NULL;
	free_pipex(structure, end);
	return (0);
}

void	free_loop(t_token *token, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token[i].type != T_NULL)
		{
			if (token[i].value != NULL)
				free(token[i].value);
			token[i].value = NULL;
			i++;
		}
		free(token);
		token = NULL;
	}
	i = 0;
	if (minishell->env)
	{
		while (minishell->env[i])
			free(minishell->env[i++]);
		i++;
		free(minishell->env);
		minishell->env = NULL;
	}
}

void	free_exit(t_token *token, t_minishell *minishell, t_pip *exec,
		int end_readline)
{
	free_loop(token, minishell);
	if (exec)
		ft_finish(exec, minishell, minishell->return_command);
	if (minishell->cwd)
	{
		free(minishell->cwd);
		minishell->cwd = NULL;
	}
	if (minishell->cwd_join)
	{
		free(minishell->cwd_join);
		minishell->cwd_join = NULL;
	}
	if (minishell->line)
	{
		free(minishell->line);
		minishell->line = NULL;
	}
	if (end_readline)
		ft_printf("exit\n");
	exit(minishell->return_command);
}

void	free_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].value && tokens[i].value != tokens[i + 1].value)
			free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
}
