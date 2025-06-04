/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 21:07:39 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "pipex.h"
#include "readline/history.h"
#include "signal.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

volatile sig_atomic_t	g_sig = 0;

void	declare_readline(t_minishell *minishell)
{

	minishell->cwd = getcwd(NULL, 0);
	if (!minishell->cwd)
		ft_free_error(minishell->cwd, "cwd error", 1, 1);
	minishell->cwd_join = ft_strjoin(minishell->cwd, "$>");
	if (minishell->cwd_join == NULL)
		ft_free_error(minishell->cwd, "cwd error", 1, 1);
	minishell->line = readline(minishell->cwd_join);
	if (minishell->line == NULL)
	{
		// free_error(minishell->tokens, minishell, 0);
		free_exit(minishell->tokens, minishell, NULL);
	}
}

void	init_minishell(t_minishell *minishell)
{
	minishell->code_error = 0;
	minishell->tokens = NULL;
	minishell->count_pipe = 0;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	minishell->nb_here_doc = 0;
	declare_readline(minishell);
}

void	minishell_env(t_minishell *minishell, char **env, int ac, char **av)
{
	minishell->env = NULL;
	(void)ac;
	(void)av;
	minishell->env = copy_original_env(env);
	if (!minishell->env)
	{
		perror("failed to set environment");
		exit(1);
	}
}

void	check_token(t_token *token, t_minishell *minishell)
{
	int	j;

	j = 0;
	if (check_parsing(token, minishell))
	{
		free_error(token, minishell, 0);
		return ;
	}
	// check_builtins(token, 0, minishell);
}

void	shift_token(t_token *token, int i)
{
	free(token[i].value);
	while (token[i + 1].value != NULL)
	{
		token[i] = token[i + 1];
		i++;
	}
	token[i].value = NULL;
	token[i].type = T_NULL;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	minishell_env(&minishell, env, ac, av);
	setup_signals();
	while (1)
	{
		init_minishell(&minishell);
		g_sig = 0;
		if (g_sig == SIGINT)
			minishell.code_error = 130;
		if (minishell.line && *minishell.line)
		{
			add_history(minishell.line);
			minishell.tokens = tokenize(minishell.line, &minishell);
			if (minishell.tokens)
			{
				setup_signals_child();
				setup_signals();
				check_token(minishell.tokens, &minishell);
				if (ft_check(minishell.tokens, 0, &minishell) == 0)
				{
					if (ft_prepare_to_pipex(&minishell, minishell.tokens) == 0)
						ft_pipex(&minishell);
					unlink_here_doc(&minishell);
					// free_error(minishell.tokens, &minishell, 0);
				}
			}
		}
		free_error(minishell.tokens, &minishell, 0);
	}
	return (0);
}
