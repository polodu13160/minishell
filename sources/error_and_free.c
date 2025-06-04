/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:56:12 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 05:16:29 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "token.h"
#include "token.h"
#include <stdio.h>

int	free_and_close(char *value1, char *value, int *save_text, int return_error)
{
	if (value1 != NULL)
		free(value1);
	free(value);
	ft_close(save_text);
	return (return_error);
}

void	*ft_error_free_tab(t_token *tab)
{
	int	i;

	i = 0;
	free(tab);
	return (NULL);
}

void	free_pipex(t_minishell *structure, int end)
{
	int	i;

	i = 0;
	if (structure->pipex)
	{
		while (structure->pipex[i].init != 1)
		{
			if (structure->pipex[i].cmd != NULL)
				free(structure->pipex[i].cmd);
			if (structure->pipex[i].infiles != NULL)
				free(structure->pipex[i].infiles);
			if (structure->pipex[i].outfiles != NULL)
				free(structure->pipex[i].outfiles);
			i++;
		}
		free(structure->pipex);
	}
	if (structure->pids != NULL)
		free(structure->pids);
	if (end > 0)
		exit(1);
}

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
	free(structure->line);
	if (structure->cwd)
		free(structure->cwd);
	if (structure->cwd_join)
		free(structure->cwd_join);
	free_pipex(structure, end);
	return (0);
}

void	ft_free_error(void *value, char *text, int perrorornot, int exitornot)
{
	free(value);
	if (perrorornot == 1)
		perror(text);
	if (exitornot == 1)
		exit(1);
}
