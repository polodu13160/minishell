/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:00:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/16 15:18:32 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include <readline/history.h>
#include <readline/readline.h>

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
	write(STDOUT_FILENO, "\n", 1);
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
