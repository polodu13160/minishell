/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/14 17:46:46 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include "parsing.h"
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

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;
	int			i;
	int			j;

	i = 0;
	(void)ac;
	(void)av;
	minishell.pipex_cmd = NULL;
	minishell.code_error = 0;
	minishell.env = env;
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
		tokens = tokenize(minishell.line, &minishell);
		if (tokens)
		{
			check_parsing(tokens, minishell);
		}
		else
		{
			free_error(token, minishell, 0);
		}
		// printf("\n%d\n", minishell.count_tokens);
		// printf("%s", tokens[minishell.count_tokens - 2].value);
		// if (check_command())
		if (ft_check(tokens, T_HEREDOC) == 1 )
			return free_error(tokens, &minishell);
		j = 0;
		while (tokens[j].value)
		{
			free(tokens[j].value);
			j++;
		}
		free(tokens);
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
		i++;
	}
	return (0);
}
