/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/22 18:08:55 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

void	check_token(t_token *token, char **env)
{
	int	i;

	(void)env;
	i = 0;
	if (!token)
	{
		printf("Error: Tokenization failed\n");
		return ;
	}
	while (token[i].value)
	{
		printf("Token %d: %s, Type: %d\n", i, token[i].value, token[i].type);
		i++;
	}
	return ;
}

int	free_error(t_token *token, t_minishell structure)
{
	int	i;

	perror("Malloc error ");
	i = 0;
	if (structure.line)
	{
		while (i < (count_tokens(structure.line) - 1) && token[i].value)
		{
			free(token[i++].value);
		}
		free(token);
		free(structure.line);
	}
	if (structure.cwd)
		free(structure.cwd);
	if (structure.cwd_join)
		free(structure.cwd_join);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_token		*token;
	t_minishell	minishell;
	int			i;
	int			j;

	(void)ac;
	(void)av;
	i = 0;
	while (i < 5)
	{
		minishell.cwd = getcwd(NULL, 0);
		// if (cwd == NULL)
		// 	create_env();
		minishell.cwd_join = ft_strjoin(minishell.cwd, "$>");
		if (minishell.cwd_join == NULL)
		{
			free(minishell.cwd);
			perror("cwd error");
			exit(1);
		}
		minishell.line = readline(minishell.cwd_join);
		if (minishell.line == NULL)
		{
			perror("readline error");
			free(minishell.cwd);
			free(minishell.cwd_join);
			exit(1);
		}
		add_history(minishell.line);
		token = tokenize(minishell.line, minishell);
		if (token)
		{
			check_token(token, env);
			j = 0;
			while (token[j].value)
			{
				free(token[j].value);
				j++;
			}
			free(token);
		}
		else
		{
			free_error(token, minishell);
		}
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
		i++;
	}
	return (0);
}
