/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 20:26:12 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "use_free.h"
#include <stdlib.h>

static void	check_expand_special(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if (tokens[i].value && tokens[i].type == T_HEREDOC)
		{
			if (tokens[i + 1].type != T_NULL && tokens[i + 1].value)
				tokens[i + 1].type = T_IGNORE;
		}
		i++;
	}
}

static void	delete_null_token_loop(t_token *tokens)
{
	int	i;

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
}

int	is_only_space(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str != 32 && (*str < 9 || *str > 13))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

static int	delete_null_token(t_token *tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i].type != T_NULL)
	{
		if ((tokens[i].type == T_ENV && ft_strncmp(tokens[i].value, "", 1) == 0)
			|| (tokens[i].value && ft_strncmp(tokens[i].value, ":", 2) == 0)
			|| (tokens[i].type == T_ENV && is_only_space(tokens[i].value)))
		{
			free(tokens[i].value);
			while (tokens[i + 1].type != T_NULL)
			{
				tokens[i] = tokens[i + 1];
				if (tokens[i].type == T_ENV)
					tokens[i].type = T_WORD;
				i++;
			}
			tokens[i].value = NULL;
			tokens[i].type = T_NULL;
			i = 0;
			break ;
		}
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

int	validate_parsing(t_token *tokens, t_minishell *minishell, int i)
{
	check_expand_special(minishell->tokens);
	if (validate_token(tokens, minishell, 0, 0))
		return (1);
	check_tokens_t_ignore(tokens);
	if (delete_null_token(minishell->tokens))
		return (1);
	while (minishell->tokens[i].type != T_NULL)
	{
		if (minishell->tokens[i].type == T_ENV)
		{
			if ((ft_strchr(minishell->tokens[i].value, ' ')
					|| ft_strchr(minishell->tokens[i].value, '\t'))
				&& !ft_strchr(minishell->tokens[i].value, '='))
			{
				if (retokenize_expanded_token(minishell->tokens, minishell, i))
					return (1);
				i = 0;
				continue ;
			}
		}
		i++;
	}
	i = 0;
	while (minishell->tokens[i].type != T_NULL)
	{
		if (minishell->tokens[i].type == T_ENV)
			minishell->tokens[i].type = T_WORD;
		i++;
	}
	get_token_index(minishell->tokens);
	return (0);
}
