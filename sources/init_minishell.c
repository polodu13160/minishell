/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:51 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/01 17:02:29 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "libft.h"
#include "parsing.h"
#include "signal.h"
#include <readline/readline.h>

void	declare_readline(t_minishell *minishell)
{
	if (minishell->cwd == NULL)
		minishell->cwd = getcwd(NULL, 0);
	if (minishell->cwd)
		minishell->cwd_join = ft_strjoin(minishell->cwd, "$> ");
	if (minishell->cwd_join == NULL)
	{	
		free_tab(minishell->env);
		ft_free_all(minishell->cwd, "cwd error", 1, 1);
	}
	minishell->line = readline(minishell->cwd_join);
	if (minishell->line == NULL)
		free_exit(minishell->tokens, minishell, NULL, 1);
}

void	init_minishell(t_minishell *minishell)
{
	minishell->tokens = NULL;
	minishell->count_pipe = 0;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	minishell->nb_here_doc = 0;
	if (g_sig == SIGINT)
	{
		minishell->return_command = 130;
	}
	declare_readline(minishell);
}

void	minishell_env(t_minishell *minishell, char **env, int ac, char **av)
{
	minishell->return_command = 0;
	minishell->env = NULL;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->tokens = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	minishell->count_pipe = 0;
	minishell->nb_here_doc = 0;
	(void)ac;
	(void)av;
	minishell->env = copy_original_env(env);
	if (!minishell->env)
	{
		perror("failed to set environment");
		exit(1);
	}
}
