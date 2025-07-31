/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:04:52 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/31 18:39:57 by antbonin         ###   ########.fr       */
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
			if (tokens[i + 1].type != T_NULL && tokens[i + 1].value)
				tokens[i + 1].type = T_IGNORE;
		}
		i++;
	}
}

void	delete_null_token_loop(t_token *tokens)
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

int	delete_null_token(t_token *tokens)
{
	int	i;

	if (!tokens)
		return (0);
	delete_null_token_loop(tokens);
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

int	delete_space_parsing(t_token *token)
{
	int	i;
	int	j;
	int	replace;

	i = 0;
	if (token[i].value[0] != 32 || token[i].value[0] < 9
		|| token[i].value[0] > 13)
		return (0);
	while (token[i].value)
	{
		replace = 0;
		j = 0;
		while (token[i].value[j] != 0 || token[i].value[j] == 32 || (token[i].value[j] >= 9
				&& token[i].value[j] <= 13))
			j++;
		while (token[i].value[j] != 0 && token[i].value[j] != 32
			&& (token[i].value[j] < 9 || token[i].value[j] > 13))
		{
			token[i].value[replace] = token[i].value[j];
			j++;
			replace++;
		}
		while (token[i].value[j] != 0  || token[i].value[j] == 32 || (token[i].value[j] >= 9
				&& token[i].value[j] <= 13))
		{
			token[i].value[replace] = '\0';
			j++;
			replace++;
		}
		i++;
	}
	return 0;
}

int	check_token(t_token *tokens, t_minishell *minishell, int i)
{
	check_expand_special(minishell->tokens);
	if (check_parsing(tokens, minishell, 0, 0))
		return (1);
	delete_space_parsing(tokens);
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
