/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/24 17:22:05 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "function.h"
#include "libft.h"
#include "limits.h"
#include "parsing.h"
#include "readline/history.h"
#include "stdbool.h"
#include "token.h"
#include <readline/readline.h>
#include <stdio.h>

int	free_error(t_token *token, t_minishell *minishell, int end)
{
	int	i;
	int	j;

	if (end == 2)
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
		if (minishell->env)
		{
			j = 0;
			while (minishell->env[j])
			{
				free(minishell->env[j]);
				j++;
			}
			free(minishell->env);
		}
		if (minishell->cwd)
			free(minishell->cwd);
		if (minishell->cwd_join)
			free(minishell->cwd_join);
		if (minishell->line)
			free(minishell->line);
		exit(minishell->code_error);
	}
	return (0);
}

// difference ;
// env print pas quand pas de =

// export , trie de a a w et
// "declare -x"

int	ft_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			if (ft_strchr(minishell->env[i], '='))
				printf("%s\n", minishell->env[i]);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	check_builtins(t_token *token, int i, t_minishell *minishell)
{
	while (token[i].value)
	{
		if (token[i].type == T_FUNC)
		{
			if (ft_strncmp(token[i].value, "echo", 5) == 0)
				minishell->code_error = ft_echo(token, i);
			else if (ft_strncmp(token[i].value, "cd", 3) == 0)
				minishell->code_error = ft_cd(token, i, minishell);
			else if (ft_strncmp(token[i].value, "exit", 5) == 0)
				minishell->code_error = ft_exit(token, minishell, 1);
			else if (ft_strncmp(token[i].value, "env", 4) == 0)
				minishell->code_error = ft_env(minishell);
			else if (ft_strncmp(token[i].value, "pwd", 4) == 0)
				printf("%s\n", getcwd(NULL, 0));
			else if (ft_strncmp(token[i].value, "export", 7) == 0)
				ft_export(token, minishell, i);
		}
		i++;
	}
}

char	**copy_original_env(char **env)
{
	int		i;
	char	**copy_env;

	i = 0;
	while (env[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 1));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy_env[i] = ft_strdup(env[i]);
		if (!copy_env[i])
		{
			while (i > 0)
				free(copy_env[--i]);
			free(copy_env);
			return (NULL);
		}
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;
	int			j;

	(void)ac;
	(void)av;
	minishell.code_error = 0;
	minishell.env = copy_original_env(env);
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
			check_parsing(tokens, &minishell);
		else
			free_error(tokens, &minishell, 0);
		j = 0;
		check_builtins(tokens, 0, &minishell);
		while (tokens[j].value)
		{
			free(tokens[j].value);
			j++;
		}
		free(tokens);
		free(minishell.cwd);
		free(minishell.cwd_join);
		free(minishell.line);
	}
	return (0);
}
