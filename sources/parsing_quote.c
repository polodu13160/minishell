/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/26 00:03:49 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token.h"

int	ft_strlen_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			j++;
		i++;
	}
	return (i - j);
}

char	*check_quote_command(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	if (str[0] == '$')
		str = ft_strtrim(str, "$");
	copy = ft_calloc(sizeof(char), (ft_strlen_quote(str) + 1));
	if (!copy)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		else
			copy[j++] = str[i++];
	}
	free(str);
	return (copy);
}

char	*parse_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	if (str[0] == '\'')
		i = 1;
	while (str[i] && str[i] != '\'')
		result[j++] = str[i++];
	free(str);
	return (result);
}

int	process_dollar(t_token *token, t_minishell *minishell, int type)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(token->value));
	if (!temp)
		return (1);
	while (token->value[++i])
		temp[i - 1] = token->value[i];
	free(token->value);
	token->value = temp;
	token->value = check_quote_command(token->value);
	if (!token->value)
		return (1);
	temp = return_env(token->value, minishell);
	if (!temp)
		return (1);
	free(token->value);
	token->value = temp;
	if (type || token->type == T_FORBID)
	{
		ft_putstr_fd("forbidden preprocessor, || or && or ; or () or \\ \n", 2);
		return (1);
	}
	return (0);
}

char	*parse_env(char *str, t_minishell *minishell)
{
	t_index	index;
	char	*result;

	index.i = 0;
	index.j = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(str) * 4 + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	while (str[index.i])
	{
		if (str[index.i] == '$')
			process_env_var(str, result, &index, minishell);
		else
			result[index.j++] = str[index.i++];
	}
	result[index.j] = '\0';
	free(str);
	return (result);
}
