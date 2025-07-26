/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/26 19:38:21 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parsing.h"
#include "pipex.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "token.h"
#include <stdio.h>

static void	main_run(t_minishell *minishell)
{
	setup_signals();
	if (tokenize(minishell->line, minishell) == 0)
	{
		if (!check_token(minishell->tokens, minishell, 0))
		{
			if (ft_check(minishell->tokens, 0, minishell) == 0)
			{
				if (ft_prepare_to_pipex(minishell, minishell->tokens) == 0)
					ft_pipex(minishell);
				unlink_here_doc(minishell);
			}
		}
	}
}

int	check_ascii_command(char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str < 0 || *str > 127)
			return (1);
		str++;
	}
	return (0);
}

static void	isatty_run(t_minishell *minishell)
{
	if (minishell->line && *minishell->line
		&& check_ascii_command(minishell->line) == 0)
	{
		add_history(minishell->line);
		main_run(minishell);
	}
	else
	{
		ft_printf_fd(2, "cannot execute binary file\n");
		minishell->return_command = 126;
		free_all(minishell->tokens, minishell, 1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	minishell_env(&minishell, env, ac, av);
	setup_signals();
	while (1)
	{
		init_minishell(&minishell);
		if (g_sig == SIGINT)
		{
			minishell.return_command = 130;
			g_sig = 0;
		}
		if (isatty(STDIN_FILENO) == 0)
			isatty_run(&minishell);
		else if (minishell.line && *minishell.line)
		{
			add_history(minishell.line);
			main_run(&minishell);
		}
		free_all(minishell.tokens, &minishell, 0);
		minishell.tokens = NULL;
		minishell.line = NULL;
	}
	return (0);
}
