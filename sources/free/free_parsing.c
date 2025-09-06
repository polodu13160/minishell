/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:56:12 by pde-petr          #+#    #+#             */
/*   Updated: 2025/09/06 15:40:41 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

void	free_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env)
	{
		while (minishell->env[i])
		{
			free(minishell->env[i]);
			i++;
		}
		free(minishell->env);
		minishell->env = NULL;
	}
}

int	free_tokens_parsing(t_token *token, int i)
{
	while (i >= 0)
	{
		if (token[i].value)
			free(token[i].value);
		token[i].value = NULL;
		i--;
	}
	return (1);
}
