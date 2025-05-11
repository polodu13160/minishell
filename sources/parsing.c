/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/11 16:15:03 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*parsing_quote(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	if (str[i] == '"' || str[i] == '\'')
		i++;
	if (str[i] == '$')
		while (str[i + j] != '"')
			j++;
	copy = malloc(sizeof(char) * j);
	if (!copy)
		return (NULL);
	j = 0;
	while(str[i] != '"')
	{
		copy[j] = str[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}

int	check_parsing(t_token *token, t_minishell minishell)
{
	int		i;
	char	*temp;

	i = 0;
	(void)minishell;
	while (token[i].value)
	{
		if (token[i].type == T_FUNC)
			token[i].value = check_quote_command(token[i].value);
		else if (token[i].type == T_ENV)
		{
			if (token[i].value[1] == '"' || token[i].value[1] == '\'')
			{
				token[i].type = T_WORD;	
				token[i].value = check_quote_command(token[i].value);
			}
			else
			{
				temp = return_env(token[i].value, minishell);
				free(token[i].value);
				token[i].value = temp;
				temp = NULL;
			}
		}
		else if (token[i].type == T_FORBID)
		{
			ft_putstr_fd("forbidden preprocessor\
		, || or && or ; or () or \\ \n", 2);
			return (1);
		}
		else if (token[i].type == T_WORD)
		{
			if (token[i].value[1] == '$')
			{
				token[i].value = check_quote_command(token[i].value);
				temp = return_env(token[i].value, minishell);
				free(token[i].value);
				token[i].value = temp;
				temp = NULL;
			}
			else if (token[i].value[0] == '"')
				token[i].value = check_quote_command(token[i].value);
		}
		ft_printf("value : %s type : %d\n", token[i].value, token[i].type);
		i++;
	}
	return (0);
}
