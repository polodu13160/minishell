/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/05 19:28:49 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "new_libft/ressource/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "stdbool.h"
#include <stdio.h>

void	check_prompt(char **prompt, char **env)
{
	char	**envp;
	char	cwd[1024];

	if (!prompt)
		return ;
	if (!ft_strncmp(prompt[0], "echo", 4))
		ft_echo(ft_aclen(prompt), prompt);
	else if (!ft_strncmp(prompt[0], "cd", 2))
		cd(prompt);
	else if (!ft_strncmp(prompt[0], "exit", 4))
		exit(0);
	else if (!ft_strncmp(prompt[0], "pwd", 3))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
	}
	else if (!ft_strncmp(prompt[0], "env", 3))
	{
		envp = env;
		while (*envp)
			printf("%s\n", *envp++);
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**prompt;
	char	buffer[1024];
	char	*cwd;

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
		prompt = ft_split(line, ' ');
		check_prompt(prompt, env);
		free(line);
	}
	return (0);
}
