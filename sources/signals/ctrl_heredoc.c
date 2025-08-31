/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:09:19 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/31 19:01:09 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int	check_sig(int statuetemp)
{
	int	sig;

	if (g_sig == SIGINT)
	{
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (WIFSIGNALED(statuetemp))
	{
		sig = WTERMSIG(statuetemp);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		return (1);
	}
	return (0);
}

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	g_sig = SIGINT;
	rl_done = 1;
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
