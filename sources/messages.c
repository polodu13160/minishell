/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:10:42 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 04:23:12 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include "stdio.h"

int	ft_print_error(t_token *tokens, int i, int error)
{
	char	*malloc_string;
	int		j;

	j = -1;
	malloc_string = NULL;
	if (error == 2)
		perror("not create tmp file");
	if (error == 3)
		perror("get_next_line error");
	if (error == 4)
		perror("write error");
	if (error == 5)
		perror("malloc error");
	else if (tokens[i + 1].value == NULL)
		printf("syntax error near unexpected token `newline'\n");
	else
	{
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n", tokens[i
			+ 1].value);
	}
	return (1);
}

int	message_error(char *first_message, char *last_message)
{
	last_message = ft_strjoin(last_message, "\n");
	if (last_message == NULL)
	{
		perror("malloc error");
		return (1);
	}
	first_message = ft_strjoin(first_message, last_message);
	if (first_message == NULL)
	{
		free(last_message);
		perror("malloc error");
		return (1);
	}
	ft_putstr_fd(first_message, 2);
	free(last_message);
	free(first_message);
	return (0);
}

void	message_output(int statuetemp, t_minishell *minishell, pid_t pidvalue)
{
	int	i;

	i = 0;
	while (pidvalue != minishell->pids[i])
		i++;
	if (WEXITSTATUS(statuetemp) != 0)
	{
		if (WEXITSTATUS(statuetemp) == 10)
			message_error("Error malloc", "in child");
		else if (WEXITSTATUS(statuetemp) == 126)
			message_error(minishell->pipex[i].cmd[0], ": Permission denied");
		else if (WEXITSTATUS(statuetemp) == 127)
		{
			if (minishell->pipex[i].cmd[0] == NULL)
				message_error("", ": Command not found");
			else
				message_error(minishell->pipex[i].cmd[0],
					": Command not found");
		}
	}
}

int	perr_and_rplce_exec_error(char *value, t_pip *exec)
{
	perror(value);
	exec->error = 1;
	return (1);
}
