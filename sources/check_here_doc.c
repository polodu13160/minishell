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

#include "token.h"
#include <stdio.h>

int	ft_print_error(t_token *tokens, int i, int error)
{
	char	*malloc_string;
	int		j;

	j = -1;
	malloc_string = NULL;
	if (error > 1)
	{
		if (error == 2)
			perror("pipe error");
		if (error == 3)
			perror("get_next_line error");
		if (error == 4)
			perror("write error");
		if (error == 5)
			perror("malloc error");
		return (1);
	}
	if (tokens[i + 1].value == NULL)
		printf("syntax error near unexpected token `newline'\n");
	else
	{
		malloc_string = ft_calloc(4, sizeof(char));
		if (malloc_string == NULL)
			return ft_print_error(tokens, i, 5);
		while (tokens[i + 1].value[++j] != 0  && j <= 2)
			malloc_string[j] = tokens[i + 1].value[j];
		printf("syntax error near unexpected token `%s'\n", malloc_string);
		free(malloc_string);
	}
	return (1);
}

int	check_command(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
		{
			if (tokens[i + 1].value == NULL)
				return (ft_print_error(tokens, i, 1));
		}
		if (tokens[i].type == T_REDIRECT_IN || tokens[i].type == T_REDIRECT_OUT
			|| tokens[i].type == T_HEREDOC || tokens[i].type == T_APPEND)
		{
			if (tokens[i + 1].type == T_WORD || tokens[i + 1].type == T_FUNC)
				return (ft_print_error(tokens, i, 1));
		}
	}
	return 0;
}

int	ft_check(t_token *tokens, int type)
{
	int	i;
	int	error;

	i = 0;
	printf("toto \n");

	while (tokens[i].value)
	{
		
		if (tokens[i].type == type)
		{
			error = ft_check_here_doc(tokens, i);
			if (error > 0)
				return (ft_print_error(tokens, i, error));
		}
		i++;
	}
	return (0);
}

int	ft_check_here_doc(t_token *tokens, int i)
{
	char	*gnl;
	int		save_text[2];
	int		j;

	j = 0;
	gnl = NULL;
	if (tokens[i].type == T_HEREDOC)
	{
		if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_FUNC)
			return (1);
		if (pipe(save_text) == -1)
			return (2);
		while (j == 0 || ft_strncmp(gnl, tokens[i + 1].value, ft_strlen(tokens[i
					+ 1].value)))
		{
			ft_putstr_fd(">", 1);
			if (j != 0)
			{
				if (write(save_text[1], tokens[i + 1].value, ft_strlen(tokens[i
							+ 1].value)) == -1)
					return (4);
				free(gnl);
			}
			j++;
			gnl = get_next_line(0);
			if (gnl == NULL)
				return (3);
		}
		close(save_text[1]);
		tokens[i].new_value = save_text;
	}
	free(gnl);
	return (0);
}
