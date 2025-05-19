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
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	ft_print_error(t_token *tokens, int i, int error)
{
	char	*malloc_string;
	int		j;
	int		*fds;

	j = -1;
	malloc_string = NULL;
	if (error > 1)
	{
		if (error == 2)
			perror("not create tmp file");
		if (error == 3)
		{
			perror("get_next_line error");
			if (tokens[i].new_value != NULL)
			{
				fds = (int *)(tokens[i].new_value);
			}
			tokens[i].new_value = NULL;
			perror("get_next_line error");
		}
		if (error == 4)
		{
			if (tokens[i].new_value != NULL)
			{
				fds = (int *)(tokens[i].new_value);
				tokens[i].new_value = NULL;
			}
			perror("write error");
		}
		if (error == 5)
			perror("malloc error");
		return (1);
		if (tokens[i + 1].value == NULL)
			printf("syntax error near unexpected token `newline'\n");
		else
		{
			malloc_string = ft_calloc(4, sizeof(char));
			if (malloc_string == NULL)
				return (ft_print_error(tokens, i, 5));
			while (tokens[i + 1].value[++j] != 0 && j <= 2)
				malloc_string[j] = tokens[i + 1].value[j];
			printf("syntax error near unexpected token `%s'\n", malloc_string);
			free(malloc_string);
		}
		return (1);
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

static char	*create_name_here_doc(void)
{
	char	*join_text1;
	char	*join_text2;
	char	*random[5];
	int		random_file;

	random[4] = 0;
	random_file = open("/dev/random", O_RDONLY);
	if (random_file < 0)
		return (NULL);
	if (read(random_file, random, 4) <= 0)
	{
		close(random_file);
		return (NULL);
	}
	join_text1 = ft_strjoin(".", (char *)random);
	if (join_text1 == NULL)
	{
		close(random_file);
		return (NULL);
	}
	join_text2 = ft_strjoin(join_text1, ".tmp");
	if (join_text2 == NULL)
		free(join_text1);
	close(random_file);	
	return (join_text2);
}

int	ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell)
{
	char	*gnl;
	int		save_text;
	char	*name_here_doc;
	int		j;

	j = 0;
	minishell->nb_here_doc++;
	gnl = NULL;
	if (tokens[i].type == T_HEREDOC)
	{
		if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_FUNC)
			return (1);
		name_here_doc = create_name_here_doc();
		if (name_here_doc == NULL)
			return (5);
		save_text = open(name_here_doc, O_WRONLY | O_CREAT | O_TRUNC, 444);
		if (save_text == -1)
		{
			free(name_here_doc);
			return (2);
		}
		tokens[i].new_value = name_here_doc;
		while (j == 0 || ft_strcmp(gnl, tokens[i + 1].value))
		{
			ft_putstr_fd(">", 1);
			if (j != 0 && (gnl != NULL && gnl[0] != 0))
			{
				if (write(save_text, gnl, ft_strlen(tokens[i + 1].value)) == -1)
				{
					free(name_here_doc);
					close(save_text);
					return (4);
				}
				free(gnl);
			}
			j++;
			gnl = get_next_line(0);
			printf("gnl value = %s", gnl);
			if (gnl == NULL)
			{
				free(name_here_doc);
				close(save_text);
				return (3);
			}
		}
		close(save_text);
		free(gnl);
	}
	return (0);
}
