/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/25 18:25:50 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "parsing.h"

void	check_expand_special(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].value && tokens[i].type == T_HEREDOC)
		{
			if (tokens[i + 1].type != T_NULL && tokens[i + 1].value && tokens[i + 1].type == T_ENV)
				tokens[i + 1].type = T_WORD;
		}
		i++;
	}
}

void	delete_null_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].value && tokens[i].value[0] == '\0')
		{
			while (tokens[i + 1].type != T_NULL)
			{
				free(tokens[i].value);
				tokens[i] = tokens[i + 1];
				i++;
			}
			tokens[i] = tokens[i + 1];
		}
		i++;
	}
}

int	check_token(t_token *tokens, t_minishell *minishell)
{
	check_expand_special(minishell->tokens);
	if (check_parsing(tokens, minishell))
		return (1);
	delete_null_token(minishell->tokens);
	return (0);
}

void	shift_token(t_token *token, int i)
{
	free(token[i].value);
	while (token[i + 1].type != T_NULL)
	{
		token[i] = token[i + 1];
		i++;
	}
	token[i].value = NULL;
	token[i].type = T_NULL;
}
