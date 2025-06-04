/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:09:53 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/28 16:03:45 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "stdio.h"

void	free_minishell(t_minishell *minishell)
{
	int	j;

	j = 0;
	if (minishell->env)
	{
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

int	free_error(t_token *token, t_minishell *minishell, int end)
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
		free_minishell(minishell);
	return (0);
}
