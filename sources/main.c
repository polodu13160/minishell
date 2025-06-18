/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/18 18:37:08 by pde-petr         ###   ########.fr       */
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
		ft_free_all(minishell->cwd, "cwd error", 1, 1);
	minishell->cwd_join = ft_strjoin(minishell->cwd, "$>");
	if (minishell->cwd_join == NULL)
		ft_free_all(minishell->cwd, "cwd error", 1, 1);
	minishell->line = readline(minishell->cwd_join);
	if (minishell->line == NULL)
		free_exit(minishell->tokens, minishell, NULL);
}

void	init_minishell(t_minishell *minishell)
{
	minishell->tokens = NULL;
	minishell->count_pipe = 0;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	minishell->nb_here_doc = 0;
	declare_readline(minishell);
	if (g_sig == SIGINT)
		minishell->return_command = 130;
}

void	minishell_env(t_minishell *minishell, char **env, int ac, char **av)
{
	minishell->return_command = 0;
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

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	minishell_env(&minishell, env, ac, av);
	while (1)
	{
		init_minishell(&minishell);
		if (minishell.line && *minishell.line)
		{
			add_history(minishell.line);
			if (tokenize(minishell.line, &minishell) == 0)
			{
				setup_signals_child();
				setup_signals();
				check_token(minishell.tokens, &minishell);
				if (ft_check(minishell.tokens, 0, &minishell) == 0)
				{
					if (ft_prepare_to_pipex(&minishell, minishell.tokens) == 0)
						ft_pipex(&minishell);
					unlink_here_doc(&minishell);
				}
			}
		}
		free_all(minishell.tokens, &minishell, 0);
	}
	return (0);
}
