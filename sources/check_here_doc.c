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

#include "builtins.h"
#include "parsing.h"
#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>

int	check_command(t_token *tokens, int i)
{
	if (tokens[i].type == T_PIPE)
	{
		if (tokens[i + 1].value == NULL || tokens[i + 1].type == T_PIPE)
			return (ft_print_error(tokens, i, 1));
	}
	if (tokens[i].type == T_REDIRECT_IN || tokens[i].type == T_REDIRECT_OUT
		|| tokens[i].type == T_HEREDOC || tokens[i].type == T_APPEND)
	{
		if (tokens[i + 1].value == NULL || (tokens[i + 1].type != T_WORD
				&& tokens[i + 1].type != T_FUNC))
		{
			return (ft_print_error(tokens, i, 1));
		}
	}
	return (0);
}

int	minishell_error(t_minishell *minishell)
{
	minishell->return_command = 130;
	return (1);
}

int	ft_check(t_token *tokens, int recurs, t_minishell *minishell)
{
	int	i;
	int	error;

	minishell->nb_here_doc = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (recurs == 1 && tokens[i].type == T_HEREDOC)
		{
			error = ft_check_here_doc(tokens, i, minishell);
			if (error == 130)
				return (minishell_error(minishell));
			if (error > 0)
				return (ft_print_error(tokens, i, error));
		}
		if (recurs == 0)
			if (check_command(tokens, i) == 1)
				return (1);
		i++;
	}
	if (recurs == 0)
		return (ft_check(tokens, ++recurs, minishell));
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

int	ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell)
{
	int		save_text;
	char	*name_here_doc;

	minishell->nb_here_doc++;
	if (tokens[i].type == T_HEREDOC)
	{
		if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_FUNC)
			return (1);
		name_here_doc = create_name_here_doc(0);
		if (name_here_doc == NULL)
			return (5);
		save_text = open(name_here_doc, O_WRONLY | O_CREAT | O_TRUNC, 446);
		if (save_text == -1)
		{
			free(name_here_doc);
			return (2);
		}
		free(tokens[i].value);
		tokens[i].value = NULL;
		tokens[i].value = name_here_doc;
		return (write_here_doc(i, 0, tokens, save_text));
	}
	return (0);
}
