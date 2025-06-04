/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 00:38:02 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

extern char	**environ;

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
		exit(1);
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
	free(structure->line);
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	free_pipex(structure, end);
	return (0);
}

void	ft_free_error(void *value, char *text, bool perrorornot, bool exitornot)
{
	free(value);
	if (perrorornot == 1)
		perror(text);
	if (exitornot == 1)
		exit(1);
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->code_error = 0;
	minishell->tokens = NULL;
	minishell->count_pipe = 0;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->env = env;
	minishell->line = NULL;
	minishell->nb_here_doc = 0;
	minishell->pids = NULL;
	minishell->pipex = NULL;
	minishell->cwd = getcwd(NULL, 0);
	minishell->cwd_join = ft_strjoin(minishell->cwd, "$>");
	if (minishell->cwd_join == NULL)
		ft_free_error(minishell->cwd, "cwd error", 1, 1);
	minishell->line = readline(minishell->cwd_join);
	if (minishell->line == NULL)
	{
		ft_free_error(minishell->cwd, "readline error", 1, 0);
		ft_free_error(minishell->cwd_join, "", 0, 1);
	}
}

void	unlink_here_doc(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->tokens[i].value)
	{
		if (minishell->tokens[i].type == T_HEREDOC)
		{
			if (ft_strncmp("/tmp", minishell->tokens[i].value, 4) == 0)
				unlink(minishell->tokens[i].value);
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;
	int			i;

	i = 0;
	(void)ac;
	(void)av;
	while (1 && i++ != 2)
	{
		init_minishell(&minishell, env);
		if (minishell.line[0] != 0)
		{
			add_history(minishell.line);
			minishell.tokens = tokenize(minishell.line, &minishell);
			if (minishell.tokens)
				check_parsing(minishell.tokens, minishell);
			else
				free_error(minishell.tokens, &minishell, 1);
			if (ft_check(minishell.tokens, 0, &minishell) == 0)
			{
				if (ft_prepare_to_pipex(&minishell, minishell.tokens) == 0)
					ft_pipex(&minishell);
				unlink_here_doc(&minishell);
				free_error(minishell.tokens, &minishell, 0);
			}
			else
				free_error(minishell.tokens, &minishell, 0);
		}
		else
			free_error(minishell.tokens, &minishell, 0);
	}
	return (0);
}
