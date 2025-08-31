/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:11:51 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/31 18:44:19 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "use_free.h"
#include <errno.h>
#include <libft.h>
#include <readline/readline.h>
#include <stdlib.h>

void	declare_readline(t_minishell *minishell)
{
	char	*itoa;
	char	*itoa_join;

	itoa = ft_itoa(minishell->return_command);
	itoa_join = ft_strjoin3(GREENBOLD "[", itoa, "]" RESET);
	if (itoa != NULL)
		free(itoa);
	if (minishell->cwd == NULL)
		minishell->cwd = getcwd(NULL, 0);
	minishell->cwd_join = ft_strjoin3(minishell->cwd, itoa_join, "$> ");
	if (itoa_join != NULL)
		free(itoa_join);
	if (minishell->cwd_join == NULL)
	{
		free_tab(minishell->env);
		free_value(minishell->cwd, "Join Error", 1, 1);
		minishell->return_command = 1;
		free_exit(minishell->tokens, minishell, NULL, 0);
	}
	minishell->line = readline(minishell->cwd_join);
	if (minishell->line == NULL)
		if (errno != 0)
			minishell->return_command = 1;
	if (minishell->line == NULL)
		free_exit(minishell->tokens, minishell, NULL, 0);
}

void	init_minishell(t_minishell *minishell)
{
	minishell->tokens = NULL;
	minishell->count_pipee = 0;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	declare_readline(minishell);
}

void	init_minishell_env(t_minishell *minishell, char **env, int ac,
		char **av)
{
	minishell->return_command = 0;
	minishell->env = NULL;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->tokens = NULL;
	minishell->line = NULL;
	minishell->pipex = NULL;
	minishell->pids = NULL;
	minishell->count_pipee = 0;
	(void)ac;
	(void)av;
	minishell->env = copy_original_env(env);
	if (!minishell->env)
	{
		perror("failed to set environment");
		exit(1);
	}
}

void	check_sig_main(t_minishell *minishell)
{
	if (g_sig != 0)
	{
		if (g_sig == 10)
			g_sig = 2;
		minishell->return_command = g_sig + 128;
		g_sig = 0;
	}
}
