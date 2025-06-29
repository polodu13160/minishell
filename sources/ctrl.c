/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:00:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/29 22:51:26 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

void	handle_sigint(int signal)
{
	(void)signal;
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_child(int signal)
{
	(void)signal;
	g_sig = SIGINT;
	rl_done = 1;
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
}

void	setup_signals_child(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_child;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
