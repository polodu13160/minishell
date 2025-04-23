/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/23 20:26:51 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

int	free_error(t_token *token, t_minishell structure, int end)
{
	int	i;

	if (end)
		perror("Malloc error ");
	i = 0;
	if (token)
	{
		while (token[i].value)
			free(token[i++].value);
		free(token);
	}
	if (end)
	{
		free(structure.line);
		if (structure.cwd)
			free(structure.cwd);
		if (structure.cwd_join)
			free(structure.cwd_join);
		exit(1);
	}
	return (0);
}

int	check_parsing(t_token *token, t_minishell minishell)
{
	int	i;

	i = 0;
	(void)minishell;
	while (token[i].value)
	{
		printf("value : %s type %d\n", token[i].value, token[i].type);
		if (token[i].type == T_FORBID)
		{
			ft_putstr_fd("forbidden preprocessor\
, || or && or ; or () or \\ \n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(void)
{
	t_token		*token;
	t_minishell	minishell;
	int			i;
	int			j;

	i = 0;
	while (1)
	{
		minishell.cwd = getcwd(NULL, 0);
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
			check_parsing(token, minishell);
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
			free_error(token, minishell, 0);
		}
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
		i++;
	}
	return (0);
}
