/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/16 17:54:50 by pde-petr         ###   ########.fr       */
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

void delete_null_token(t_token *tokens)
{
	int i;
	i = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].value[0] == '\0')
		{
			while (tokens[i+1].value != NULL)
			{
				free(tokens[i].value);
				tokens[i] = tokens[i+1];
				i++;
			}
			tokens[i] = tokens[i+1];
		}
		i++;
	}
}

void	check_token(t_token *tokens, t_minishell *minishell)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	check_expand_special(minishell->tokens);
	if (check_parsing(tokens, minishell))
	{
		free_all(tokens, minishell, 0);
		return ;
	}
	delete_null_token(minishell->tokens);
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
