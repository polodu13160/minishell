/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:00:11 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/31 16:00:28 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "use_free.h"
#include <stdlib.h>

int	minishell_ctrl_c(t_minishell *minishell)
{
	minishell->return_command = 130;
	return (1);
}

int	print_error(t_minishell *minishell, t_token *tokens, int i, int error)
{
	char	*malloc_string;

	malloc_string = NULL;
	minishell->return_command = 2;
	if (error == 130)
		return (minishell_ctrl_c(minishell));
	if (error == 2)
		perror("not create tmp file");
	else if (error == 3)
		ft_printf_fd(2, "here-document delimited by end-of-file\n");
	else if (error == 4)
		perror("write error or close error");
	else if (error == 5)
		perror("malloc error");
	else if (tokens[i + 1].value == NULL || tokens[i + 1].value[0] == '\0')
		printf("syntax error near unexpected token `newline'\n");
	else
	{
		if (tokens[i].type != T_PIPE)
			i++;
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n",
			tokens[i].value);
	}
	return (1);
}

int	message_error(char *first_message, char *last_message)
{
	last_message = ft_strjoin(last_message, "\n");
	if (last_message == NULL)
	{
		perror("Error Malloc");
		return (1);
	}
	first_message = ft_strjoin(first_message, last_message);
	if (first_message == NULL)
	{
		free(last_message);
		perror("Error Malloc");
		return (1);
	}
	ft_putstr_fd(first_message, 2);
	free(last_message);
	free(first_message);
	return (0);
}

int	message_error_output(t_minishell *minishell, t_pipe *exec, int value_return,
		char *cmd)
{
	if (value_return == 2)
		message_error(".: filename argument required \n",
			".: usage: . filename [arguments]");
	if (value_return == 8)
	{
		message_error("Error dup", "");
		finish_child(minishell, exec, value_return);
	}
	if (value_return == 10)
		message_error("Error malloc", "");
	else if (value_return == 126)
		message_error(cmd, ": Permission denied");
	else if (value_return == 127)
	{
		if (cmd == NULL)
			message_error("", ": Command not found");
		else
			message_error(cmd, ": Command not found");
	}
	return (value_return);
}
