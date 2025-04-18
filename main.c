/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/18 18:47:23 by antbonin         ###   ########.fr       */
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
	int	i;
	int	j;

	(void)env;
	i = 0;
	if (!token)
	{
		printf("Error: Tokenization failed\n");
		return ;
	}
	while (token[i].value)
	{
		printf("Token %d: %s, Type: %d\n", i, token[i].value, token[i].type);
		i++;
	}
	j = 0;
	while (token[j].value)
	{
		free(token[j].value);
		j++;
	}
	free(token);
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*cwd;
	t_token	*token;

	(void)ac;
	(void)av;
	while (1)
	{
		cwd = ft_strjoin(getcwd(NULL, 0), "$>");
		line = readline(cwd);
		if (line == NULL)
		{
			printf("Error: readline failed\n");
			continue ;
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
