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

#include "pipex.h"
#include "token.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>

extern char	**environ;

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

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (s1[ft_strlen(s1) - 1] == '\n')
		s1[ft_strlen(s1) - 1] = '\0';
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

int	free_and_close(char *value1, char *value, int *save_text, int return_error)
{
	if (value1 != NULL)
		free(value1);
	free(value);
	ft_close(save_text);
	return return_error;
}

int	write_here_doc(int i, int j, t_token *tokens, int save_text)
{
	char	*read_like_gnl;

	read_like_gnl = NULL;
	while (j++ == 0 || read_like_gnl[0] == 0 || ft_strcmp(read_like_gnl,
			tokens[i + 1].value))
	{
		if (j != 0)
		{
			if ((read_like_gnl != NULL) && (write(save_text, read_like_gnl,
						ft_strlen(read_like_gnl)) == -1 || write(save_text,
						"\n", 1) == -1))
				return (free_and_close(read_like_gnl, tokens[i].value,
						&save_text, 4));
			free(read_like_gnl);
		}
		read_like_gnl = readline(">");
		if (read_like_gnl == NULL)
			return (free_and_close(read_like_gnl, tokens[i].value, &save_text,
					3));
	}
	ft_close(&save_text);
	free(read_like_gnl);
	return (0);
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
		tokens[i].value = name_here_doc;
		return (write_here_doc(i, 0, tokens, save_text));
	}
	return (0);
}
