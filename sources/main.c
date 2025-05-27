/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/27 17:10:33 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
#include "parsing.h"
#include "readline/history.h"
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
	char	*cwd;

	while (token[i].value)
	{
		if (token[i].type == T_FUNC)
		{
			if (ft_strncmp(token[i].value, "echo", 5) == 0)
				minishell->code_error = ft_echo(token, i);
			else if (ft_strncmp(token[i].value, "cd", 3) == 0)
				minishell->code_error = ft_cd(token, i, minishell);
			else if (ft_strncmp(token[i].value, "exit", 5) == 0)
				ft_exit(token, minishell, 1);
			else if (ft_strncmp(token[i].value, "env", 4) == 0)
				minishell->code_error = ft_env(minishell);
			else if (ft_strncmp(token[i].value, "pwd", 4) == 0)
			{
				cwd = getcwd(NULL, 0);
				printf("%s\n", cwd);
				free(cwd);
			}
			else if (ft_strncmp(token[i].value, "export", 7) == 0)
				ft_export(token, minishell, i);
			else if (ft_strncmp(token[i].value, "unset", 6) == 0)
				ft_unset(token, minishell, i);
		}
		i++;
	}
}

char	**copy_original_env(char **env)
{
	int		i;
	char	**copy_env;
	int		shlvl_value;
	char	*shlvl_str;
	char	*pwd;

	shlvl_value = 0;
	shlvl_str = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	i = 0;
	if (!env || !env[0])
	{
		copy_env = malloc(sizeof(char *) * 3);
		if (!copy_env)
			return (NULL);
		copy_env[0] = ft_strjoin("PWD=", pwd);
		copy_env[1] = ft_strdup("SHLVL=1");
		if (!copy_env[0] || !copy_env[1])
		{
			free(copy_env);
			free(pwd);
			return (NULL);
		}
		copy_env[2] = NULL;
		free(pwd);
		return (copy_env);
	}
	while (env[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 1));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = ft_atoi(env[i] + 6, 0) + 1;
			shlvl_str = ft_itoa(shlvl_value);
			copy_env[i] = ft_strjoin("SHLVL=", shlvl_str);
			free(shlvl_str);
		}
		else
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
	free(pwd);
	return (copy_env);
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;
	int			j;
	int			i;

	tokens = NULL;
	(void)ac;
	(void)av;
	minishell.env = NULL;
    minishell.cwd = NULL;
    minishell.cwd_join = NULL;
    minishell.line = NULL;
    minishell.code_error = 0;
	minishell.env = copy_original_env(env);
	if (!minishell.env)
	{
		perror("failed to set environment");
		exit(1);
	}
	i = 0;
	while (1)
	{
		minishell.cwd = getcwd(NULL, 0);
		if (!minishell.cwd)
		{
			perror("getcwd error in main loop");
			free_error(tokens, &minishell, 1);
		}
		minishell.cwd_join = NULL; // ft_strjoin(minishell.cwd, "$>");
		if (!minishell.cwd_join)
		{
			perror("cwd error");
			free_error(tokens, &minishell, 1);
			exit(1);
		}
		minishell.line = readline(minishell.cwd_join);
		if (!minishell.line)
		{
			perror("readline error");
			free(minishell.cwd);
			free(minishell.cwd_join);
			free_error(tokens, &minishell, 1);
		}
		add_history(minishell.line);
		tokens = tokenize(minishell.line, &minishell);
		if (tokens)
		{
			check_parsing(tokens, &minishell);
			j = 0;
			while (tokens[j].value)
			{
				free(tokens[j].value);
				j++;
			}
			free(tokens);
		}
		else
			free_error(tokens, &minishell, 0);
		j = 0;
		if (tokens)
			check_builtins(tokens, 0, &minishell);
		else
			free_error(tokens, &minishell, 0);
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
