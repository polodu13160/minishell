/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/22 21:11:02 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

extern char	**environ;

int	free_error(t_token *token, t_minishell *structure, int end)
{
	int	i;

	if (end == 2)
		perror("Malloc error ");
	i = 0;
	if (token)
	{
		while (token[i].value)
		{
			free(token[i].new_value);
			free(token[i++].value);
		}
		free(token);
	}
	free(structure->line);
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	if (end > 0)
	{
		exit(1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;
	int			i;
	int			j;

	i = 0;
	(void)ac;
	(void)av;
	minishell.code_error = 0;
	minishell.env = env;
	tokens = NULL;
	while (1 && i != 4)
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
		if (minishell.line[0] != 0)
		{
			add_history(minishell.line);
			tokens = tokenize(minishell.line, &minishell);
			if (tokens)
			{
				check_parsing(tokens, minishell);
			}
			else
			{
				free_error(tokens, &minishell, 0);
			}
			if (ft_check(tokens, 0, &minishell) == 0)
			{
				free_error(tokens, &minishell, 0);
				if (ft_prepare_to_pipex(&minishell, tokens))
				{
					
				}
				
				
			}
			else
			{
				free_error(tokens, &minishell, 1);
			}
		}
		else
			free_error(tokens, &minishell, 0);
		j = 0;
		i++;
	}
	return (0);
}
