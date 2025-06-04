/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 04:31:15 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include "pipex.h"
#include <readline/readline.h>
#include <stdio.h>

extern char	**environ;


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
				{
					dprintf(2,"toto\n");
					ft_pipex(&minishell);
				}
				dprintf(2,"toto1\n");
				unlink_here_doc(&minishell);
				dprintf(2,"toto2\n");
				free_error(minishell.tokens, &minishell, 0);
				dprintf(2,"toto3\n");
			}
			else
				free_error(minishell.tokens, &minishell, 0);
		}
		else
			free_error(minishell.tokens, &minishell, 0);
	}
	return (0);
}
