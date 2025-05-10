/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/07 13:46:18 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

void	check_token(t_token *tokens, char **env)
{
	int	i;

	(void)env;
	i = 0;
	if (!tokens)
	{
		printf("Error: Tokenization failed\n");
		return ;
	}
	while (tokens[i].value)
	{
		printf("Token %d: %s, Type: %d\n", i, tokens[i].value, tokens[i].type);
		i++;
	}
	return ;
}

int	free_error(t_token *tokens, t_minishell *structure)
{
	int	i;
	int	j;

	i = 0;
	if (structure->line)
	{
		while (i < (count_tokens(structure->line) - 1) && tokens[i].value)
		{
			free(tokens[i++].value);
		}
		free(tokens);
		free(structure->line);
	}
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	i = 0;
	while (structure->pipex_cmd != NULL && structure->pipex_cmd[i] != NULL)
	{
		j = 0;
		free(structure->pipex_cmd[i]);
		i++;
	}
	if (structure->pipex_cmd != NULL)
		free(structure->pipex_cmd);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
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
		tokens = tokenize(minishell.line, &minishell);
		if (tokens)
		{
			check_token(tokens, env);
		}
		else
		{
			perror("Malloc error ");
			free_error(tokens, &minishell);
		}
		// printf("\n%d\n", minishell.count_tokens);
		// printf("%s", tokens[minishell.count_tokens - 2].value);
		if (ft_ast_token(tokens, &minishell) == 1)
			free_error(tokens, &minishell);
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
