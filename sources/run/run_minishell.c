/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:50:18 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 19:43:38 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline/history.h"
#include "readline/readline.h"

void	main_run(t_minishell *minishell)
{
	setup_signals();
	if (tokenize(minishell->line, minishell) == 0)
	{
		if (!validate_parsing(minishell->tokens, minishell, 0))
		{
			if (ft_check(minishell->tokens, 0, minishell) == 0)
			{
				
				if (ft_prepare_to_pipex(minishell, minishell->tokens) == 0)
					ft_pipex(minishell);
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

void	isatty_run(t_minishell *minishell)
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
