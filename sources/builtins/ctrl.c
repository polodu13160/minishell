/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:00:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/05 02:08:42 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
# include "readline/readline.h"
#include "unistd.h"

volatile sig_atomic_t	g_sig = 0;

int	in_process_marker(void)
{
	return (0);
}

void	handle_sigint(int signal)
{
	(void)signal;
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_child(int signal)
{
	(void)signal;
	g_sig = SIGINT;
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
	signal(SIGQUIT, SIG_DFL);
}
