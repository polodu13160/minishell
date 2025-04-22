/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:06 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/21 22:53:36 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "libft.h"
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

int free_and_finish(char *malloc, )
{
	
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*cwd;
	t_token	*token;
	char	*cwd_join;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	while (1 && i != 3)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			create_env();
		cwd_join = ft_strjoin(cwd, "$>");
		if (cwd_join == NULL)
		{
			free(cwd);
			perror("cwd error");
			break ;
		}
		line = readline(cwd_join);
		if (line == NULL)
		{
			perror("readline error");
			free(cwd);
			free(cwd_join);
			break ;
		}
		else
		{
			if (!*line)
				free(line);
			add_history(line);
			token = tokenize(line);
			check_token(token, env);
		}
		free(cwd);
		free(cwd_join);
		i++;
	}
	free(line);
	return (0);
}
