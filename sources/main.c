/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 15:02:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "token.h"
#include "use_free.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	init_minishell_env(&minishell, env, ac, av);
	setup_signals();
	while (1)
	{
		init_minishell(&minishell);
		if (g_sig != 0)
		{
			if (g_sig == 10)
				g_sig = 2;
			minishell.return_command = g_sig + 128;
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
	rl_clear_history();
	return (0);
}
