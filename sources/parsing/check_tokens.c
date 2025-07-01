/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/01 20:32:44 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "libft.h"
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
				tokens[i + 1].type = T_IGNORE;
		}
		i++;
	}
}

int	delete_null_token(t_token *tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if ((tokens[i].type == T_ENV && ft_strncmp(tokens[i].value, "", 1) == 0)
			|| (tokens[i].value && ft_strncmp(tokens[i].value, ":", 2) == 0))
		{
			free(tokens[i].value);
			while (tokens[i + 1].type != T_NULL)
			{
				tokens[i] = tokens[i + 1];
				i++;
			}
			tokens[i].value = NULL;
			tokens[i].type = T_NULL;
			break ;
		}
		i++;
	}
	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].type == T_ENV)
			tokens[i].type = T_WORD;
		i++;
	}
	return (0);
}

static void	check_tokens_t_ignore(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].type == T_IGNORE)
			tokens[i].type = T_WORD;
		i++;
	}
}

int	check_token(t_token *tokens, t_minishell *minishell, int i)
{
	check_expand_special(minishell->tokens);
	if (check_parsing(tokens, minishell, 0, 0))
		return (1);
	i = 0;
	check_tokens_t_ignore(tokens);
	while (minishell->tokens[i].type != T_NULL)
	{
		if (minishell->tokens[i].type == T_ENV)
		{
			if (ft_strchr(minishell->tokens[i].value, ' ')
				|| ft_strchr(minishell->tokens[i].value, '\t'))
			{
				if (retokenize(minishell->tokens, minishell, i))
					return (1);
				i = 0;
				continue ;
			}
		}
		i++;
	}
	if (delete_null_token(minishell->tokens))
		return (1);
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
