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
#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>


extern char **environ;

int	ft_print_error(t_token *tokens, int i, int error)
{
	char	*malloc_string;
	int		j;

	j = -1;
	malloc_string = NULL;
	if (error > 1)
	{
		if (error == 2)
			perror("not create tmp file");
		if (error == 3)
		{
			
			perror("get_next_line error");
		}
		if (error == 4)
		{
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
			ft_printf_fd(2, "syntax error near unexpected token `%s'\n",
				malloc_string);
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

// int	check_env(char *read_like_gnl)
// {
// 	int		i;
// 	int		j;
// 	char	*value_strenv;
// 	char *value_env;

// 	i = 0;
// 	j = 0;
// 	while (read_like_gnl[i])
// 	{
// 		if (read_like_gnl[i] == '$' && (ft_isalpha(read_like_gnl[i]) == 0
// 				|| ft_isalnum(read_like_gnl[i]) == 0
// 				|| read_like_gnl[i] == '_'))
// 		{
// 			j = i++;
// 			while (ft_isalpha(read_like_gnl[j]) == 0
// 				|| ft_isalnum(read_like_gnl[j]) == 0 || read_like_gnl[j] == '_')
// 				j++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (j > 0)
// 	{
// 		value_strenv = ft_substr(read_like_gnl, i, j);
// 		value_env = get_env_value(value_env, environ);
// 		if (value_strenv== NULL || value_env == NULL)
// 		{
// 			free(value_strenv);
// 			return 5;
// 		}
		


			
// 		// free(var_name);
// 		// k = 0;
// 		// while (value && value[k])
// 		// 	result[(index->j)++] = value[k++];
// 		// free(value);
// 		// index->i += var_len;
// 	}
// }

int	ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell)
{
	char	*read_like_gnl;
	int		save_text;
	char	*name_here_doc;
	int		j;

	j = 0;
	minishell->nb_here_doc++;
	read_like_gnl = NULL;
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
		while (j == 0 || read_like_gnl[0] == 0 || ft_strcmp(read_like_gnl,
				tokens[i + 1].value))
		{
			ft_putstr_fd(">", 1);
			if (j != 0)
			{
				if ((read_like_gnl != NULL && read_like_gnl[0] != 0) && write(save_text,
						read_like_gnl, ft_strlen(read_like_gnl)) == -1)
				{
					free(name_here_doc);
					close(save_text);
					return (4);
				}
				free(read_like_gnl);
			}
			j++;
			read_like_gnl = readline(0);
			if (read_like_gnl == NULL)
			{
				free(name_here_doc);
				close(save_text);
				return (3);
			}
		}
		free(tokens[i].value);
		tokens[i].value = name_here_doc;
		close(save_text);
		free(read_like_gnl);
	}
	return (0);
}
