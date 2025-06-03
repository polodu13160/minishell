/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/03 01:55:38 by pde-petr         ###   ########.fr       */
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

int	free_error(t_token *token, t_minishell *structure, int end)
{
	int	i;

	if (end == 2)
		perror("Malloc error ");
	i = 0;
	if (token)
	{
		while (token[i].value)
		{
			free(token[i++].value);
		}
		free(token);
	}
	free(structure->line);
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	i = 0;
	if (structure->pipex)
	{
		while (structure->pipex[i].init != 1)
		{
			free(structure->pipex[i].cmd);
			free(structure->pipex[i].infiles);
			free(structure->pipex[i].outfiles);
			i++;
		}
		free(structure->pipex);
	}
	if (structure->pids != NULL)
		free(structure->pids);
	if (end > 0)
	{
		exit(1);
	}
	return (0);
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
	int			j;

	i = 0;
	(void)ac;
	(void)av;
	while (1 && i != 1)
	{
		init_minishell(&minishell, env);
		minishell.cwd = getcwd(NULL, 0);
		minishell.cwd_join = ft_strjoin(minishell.cwd, "$>");
		if (minishell.cwd_join == NULL)
		{
			free(minishell.cwd);
			perror("cwd error");
			exit(1);
		}
		minishell.line = readline(minishell.cwd_join);
		if (minishell.line == NULL)
		{
			perror("readline error");
			free(minishell.cwd);
			free(minishell.cwd_join);
			exit(1);
		}
		if (minishell.line[0] != 0)
		{
			add_history(minishell.line);
			minishell.tokens = tokenize(minishell.line, &minishell);
			if (minishell.tokens)
			{
				check_parsing(minishell.tokens, minishell);
			}
			else
			{
				free_error(minishell.tokens, &minishell, 0);
			}
			if (ft_check(minishell.tokens, 0, &minishell) == 0)
			{
				if (ft_prepare_to_pipex(&minishell, minishell.tokens) == 0)
				{
					ft_pipex(&minishell);
					// free_error(minishell.tokens, &minishell, 0);
				}
				unlink_here_doc(&minishell);
				free_error(minishell.tokens, &minishell, 0);
				dprintf(2,"\nddd\n");
			}
			else
			{
				free_error(minishell.tokens, &minishell, 1);
			}
		}
		else
			free_error(minishell.tokens, &minishell, 0);
		j = 0;
		i++;
	}
	return (0);
}
