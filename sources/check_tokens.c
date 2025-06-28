/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/28 18:35:18 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "parsing.h"

void	check_expand_special(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].value && tokens[i].type == T_HEREDOC)
		{
			if (tokens[i + 1].type != T_NULL && tokens[i + 1].value && tokens[i
					+ 1].type == T_ENV)
				tokens[i + 1].type = T_WORD;
		}
		i++;
	}
}

void	delete_null_token(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i].type != T_NULL)
		{
			if (tokens[i].value && tokens[i].value[0] == '\0')
			{
				while (tokens[i + 1].type != T_NULL)
				{
					free(tokens[i].value);
					tokens[i].value = NULL;
					tokens[i] = tokens[i + 1];
					i++;
				}
				tokens[i] = tokens[i + 1];
			}
			i++;
		}
	}
}

int	check_token(t_token *tokens, t_minishell *minishell)
{
	int	i;

	check_expand_special(minishell->tokens);
	if (check_parsing(tokens, minishell, 0, 0))
		return (1);
	i = 0;
	while (minishell->tokens[i].type != T_NULL)
	{
		if (minishell->tokens[i].type == T_ENV)
		{
			if (ft_strchr(minishell->tokens[i].value, ' '))
			{
				if (retokenize(minishell->tokens, minishell, i))
					return (1);
				i = 0;
				continue ;
			}
			else
				minishell->tokens[i].type = T_WORD;
		}
		i++;
	}
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
