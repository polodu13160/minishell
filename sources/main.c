/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 16:53:41 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
#include "signal.h"
#include "token.h"
#include "pipex.h"
#include <readline/readline.h>
#include <stdio.h>

volatile sig_atomic_t	g_sig = 0;

void	declare_minishell(t_minishell *minishell, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell->env = NULL;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->code_error = 0;
	minishell->env = copy_original_env(env);
	if (!minishell->env)
	{
		perror("failed to set environment");
		exit(1);
	}
}

void	readline_declare(t_token *tokens, t_minishell *minishell)
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

	i = 0;
	tokens = NULL;
	declare_minishell(&minishell, ac, av, env);
	setup_signals();
	while (1)
	{
		g_sig = 0;
		readline_declare(tokens, &minishell);
		if (g_sig == SIGINT)
			minishell.code_error = 130;
		if (minishell.line && *minishell.line)
		{
			add_history(minishell.line);
			tokens = tokenize(minishell.line, &minishell);
			if (tokens)
			{
				setup_signals_child();
				check_token(tokens, &minishell);
				setup_signals();
				tokens = NULL;
			}
		}
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
	}
	return (0);
}
