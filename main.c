/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/15 18:35:17 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "new_libft/ressource/libft.h"
#include "readline/history.h"
#include "stdbool.h"
#include <readline/readline.h>
#include <stdio.h>

void	check_token(t_token *token, char **env)
{
	int		i;
	// char	**envp;
	// char	cwd[1024];
	(void)env;

	i = 0;
	while (token[i].value)
	{
		printf("Token: %s, Type: %d\n", token[i].value, token[i].type);
		i++;
	}
	while (token[i].value)
	{
		free(token[i].value);
		i++;
	}
	free(token);
	// if (!prompt)
	// 	return ;
	// if (!ft_strncmp(prompt[0], "echo", 4))
	// 	ft_echo(ft_aclen(prompt), prompt);
	// else if (!ft_strncmp(prompt[0], "cd", 2))
	// 	cd(prompt);
	// else if (!ft_strncmp(prompt[0], "exit", 4))
	// 	exit(0);
	// else if (!ft_strncmp(prompt[0], "pwd", 3))
	// {
	// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
	// 		printf("%s\n", cwd);
	// }
	// else if (!ft_strncmp(prompt[0], "env", 3))
	// {
	// 	envp = env;
	// 	while (*envp)
	// 		printf("%s\n", *envp++);
	// }
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	buffer[1024];
	char	*cwd;
	t_token	*token;

	(void)ac;
	(void)av;
	while (1)
	{
		cwd = ft_strjoin(getcwd(buffer, sizeof(buffer)), "$>");
		line = readline(cwd);
		if (line == NULL)
		{
			printf("Error: readline failed\n");
			return (1);
		}
		add_history(line);
		if (!*line)
		{
			free(line);
			continue ;
		}
		token = tokenize(line);
		check_token(token, env);
	}
	return (0);
}
