/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/23 18:12:16 by antbonin         ###   ########.fr       */
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

int	free_error(t_token *token, t_minishell *structure, int end)
{
	int	i;

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
		free(structure->line);                                                            
		if (structure->cwd)
			free(structure->cwd);
		if (structure->cwd_join)
			free(structure->cwd_join);
		if (structure->env && structure->env_copied)
		{
			i = 0;
			while (structure->env[i])
			{
				free(structure->env[i]);
				i++;
			}
			free(structure->env);
		}
		exit(structure->code_error);
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

int	ft_export(t_token *token, t_minishell *minishell, int i)
{
	int		j;
	char	**new_env;
	char	*var_name;
	int		name_len;
	int		exists;
	char	*temp;

	if (!token[i + 1].value)
	{
		j = 0;
		while (minishell->env[j])
		{
			printf("declare -x %s\n", minishell->env[j]);
			j++;
		}
		return (0);
	}
	var_name = token[i + 1].value;
	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	exists = -1;
	j = 0;
	while (minishell->env[j])
	{
		if (ft_strncmp(minishell->env[j], var_name, name_len) == 0
			&& (minishell->env[j][name_len] == '='
				|| minishell->env[j][name_len] == '\0'))
		{
			exists = j;
			break ;
		}
		j++;
	}
	if (exists >= 0)
	{
		temp = ft_strdup(token[i + 1].value);
		if (!temp)
			return (1);
		free(minishell->env[exists]);
		minishell->env[exists] = temp;
		return (0);
	}
	j = 0;
	while (minishell->env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 2));
	if (!new_env)
		return (1);
	j = 0;
	while (minishell->env[j])
	{
		new_env[j] = minishell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(token[i + 1].value);
	if (!new_env[j])
	{
		free(new_env);
		return (1);
	}
	new_env[j + 1] = NULL;
	if (minishell->env_copied)
		free(minishell->env);
	minishell->env = new_env;
	minishell->env_copied = 1;
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
				minishell->code_error = ft_exit(token, minishell, i);
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

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_minishell	minishell;
	int			j;

	(void)ac;
	(void)av;
	minishell.code_error = 0;
	minishell.env = env;
	minishell.env_copied = 0;
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
