/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:09:19 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/05 17:55:38 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	check_sig(int statuetemp)
{
	int	sig;

	if (g_sig == SIGINT)
	{
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (WIFSIGNALED(statuetemp))
	{
		sig = WTERMSIG(statuetemp);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
}

void	setup_signals_heredoc(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_child;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
