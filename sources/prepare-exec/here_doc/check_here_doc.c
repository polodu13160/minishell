/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:08:24 by paul              #+#    #+#             */
/*   Updated: 2025/05/11 21:08:25 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <stdlib.h>

int	check_command(t_token *tokens, int i, t_minishell *minishell)
{
	if (tokens[i].type == T_PIPE)
	{
		if (i == 0 || tokens[i + 1].value == NULL || tokens[i
				+ 1].type == T_PIPE)
		{
			minishell->return_command = 1;
			return (print_error(minishell, tokens, i, 1));
		}
	}
	if (tokens[i].type == T_REDIRECT_IN || tokens[i].type == T_REDIRECT_OUT
		|| tokens[i].type == T_HEREDOC || tokens[i].type == T_APPEND)
	{
		if (tokens[i + 1].value == NULL || (tokens[i + 1].type != T_WORD
				&& tokens[i + 1].type != T_FUNC && tokens[i
					+ 1].type != T_AMBIGOUS))
		{
			minishell->return_command = 1;
			return (print_error(minishell, tokens, i, 1));
		}
	}
	return (0);
}

int	check(t_token *tokens, int recurs, t_minishell *minishell)
{
	int	i;
	int	error;

	i = -1;
	while (tokens[++i].value)
	{
		if (recurs == 1 && tokens[i].type == T_HEREDOC)
		{
			error = check_here_doc(tokens, i, minishell);
			if (error > 0)
			{
				if (error == 3)
					print_error(minishell, tokens, i, error);
				else
					return (print_error(minishell, tokens, i, error));
			}
		}
		if (recurs == 0)
			if (check_command(tokens, i, minishell) == 1)
				return (1);
	}
	if (recurs == 0)
		return (check(tokens, ++recurs, minishell));
	return (0);
}

static char	*create_name_here_doc(int i)
{
	char	*join_text1;
	char	*itoa_char;

	itoa_char = ft_itoa(i);
	if (itoa_char == NULL)
		return (NULL);
	join_text1 = ft_strjoin("/tmp/.", itoa_char);
	free(itoa_char);
	if (join_text1 == NULL)
		return (NULL);
	if (access(join_text1, F_OK) == 0)
	{
		free(join_text1);
		return (create_name_here_doc(++i));
	}
	return (join_text1);
}

int	check_here_doc(t_token *tokens, int i, t_minishell *minishell)
{
	int		save_text;
	int		read_text;
	char	*name_here_doc;

	if (tokens[i].type == T_HEREDOC)
	{
		if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_FUNC)
			return (1);
		name_here_doc = create_name_here_doc(0);
		if (name_here_doc == NULL)
			return (5);
		save_text = open(name_here_doc, O_WRONLY | O_CREAT, 0666);
		read_text = open(name_here_doc, O_RDONLY, 0666);
		free(tokens[i].value);
		tokens[i].value = name_here_doc;
		if (save_text == -1 || read_text == -1)
		{
			close_2_fds(&save_text, &read_text);
			return (2);
		}
		unlink(minishell->tokens[i].value);
		tokens[i].fd = read_text;
		return (write_here_doc(i, tokens, save_text));
	}
	return (0);
}
