/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/16 15:44:20 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "parsing.h"

void	check_expand_special(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == T_HEREDOC)
		{
			if (tokens[i + 1].value != NULL && tokens[i + 1].type == T_ENV)
				tokens[i + 1].type = T_WORD;
		}
		i++;
	}
}

void	check_token(t_token *token, t_minishell *minishell)
{
	int	j;

	j = 0;
	check_expand_special(minishell->tokens);
	if (check_parsing(token, minishell))
	{
		free_error(token, minishell, 0);
		return ;
	}
}

void	shift_token(t_token *token, int i)
{
	free(token[i].value);
	while (token[i + 1].value != NULL)
	{
		token[i] = token[i + 1];
		i++;
	}
	token[i].value = NULL;
	token[i].type = T_NULL;
}
