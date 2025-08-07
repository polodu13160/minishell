/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:00:28 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 20:44:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

int	check_interrupt(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	handle_sigint(int signal)
{
	(void)signal;
	if (rl_done == 1)
		write(STDOUT_FILENO, "\n", 1);
	else if (rl_done != 1)
	{
		g_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigint_child(int signal)
{
	(void)signal;
	if (g_sig == 10)
	{
		g_sig = 10;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (rl_done == 1)
		write(STDOUT_FILENO, "\n", 1);
	else if (rl_done != 1)
	{
		g_sig = SIGINT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
}

void	setup_signals_child(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_DFL);
}
