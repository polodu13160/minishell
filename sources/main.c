/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/27 19:18:53 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

void	declare_minishell(t_minishell *minishell, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell->env = NULL;
	minishell->cwd = NULL;
	minishell->cwd_join = NULL;
	minishell->line = NULL;
	minishell->code_error = 0;
	minishell->env = copy_original_env(env);
	if (!minishell->env)
	{
		perror("failed to set environment");
		exit(1);
	}
}

void	readline_declare(t_token *tokens, t_minishell *minishell)
{
	minishell->cwd = getcwd(NULL, 0);
	if (!minishell->cwd)
		free_error(tokens, minishell, 1);
	minishell->cwd_join = ft_strjoin(minishell->cwd, "$>");
	if (!minishell->cwd_join)
		free_error(tokens, minishell, 1);
	minishell->line = readline(minishell->cwd_join);
	if (!minishell->line)
		free_error(tokens, minishell, 1);
}

void	check_token(t_token *token, t_minishell *minishell)
{
	int	j;

	j = 0;
	if (check_parsing(token, minishell))
	{
		free_error(token, minishell, 0);
		return ;
	}
	check_builtins(token, 0, minishell);
	while (token[j].value)
	{
		free(token[j].value);
		j++;
	}
	free(token);
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;

	tokens = NULL;
	declare_minishell(&minishell, ac, av, env);
	while (1)
	{
		readline_declare(tokens, &minishell);
		add_history(minishell.line);
		tokens = tokenize(minishell.line, &minishell);
		if (tokens)
			check_token(tokens, &minishell);
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
	}
	return (0);
}
