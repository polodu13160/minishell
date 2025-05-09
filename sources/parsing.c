/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/09 18:37:45 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_parsing(t_token *token, t_minishell minishell)
{
	int		i;
	char	*env_value;
	char	*unquoted;
	char	*expanded;

	i = 0;
	(void)minishell;
	while (token[i].value)
	{
		if (token[i].type == T_FUNC)
			token[i].value = check_quote_command(token[i].value);
		else if (token[i].type == T_ENV)
		{
			env_value = return_env(token, i, minishell);
			free(token[i].value);
			token[i].value = env_value;
		}
		else if (token[i].type == T_FORBID)
		{
			ft_putstr_fd("forbidden preprocessor\
		, || or && or ; or () or \\ \n", 2);
			return (1);
		}
		else if (token[i].type == T_WORD)
		{
			if (token[i].value[0] == '\"')
			{
				unquoted = ft_substr(token[i].value, 1,
						ft_strlen(token[i].value) - 2);
				expanded = expand_env_vars(&token[i].type, unquoted, minishell);
				free(unquoted);
				free(token[i].value);
				token[i].value = expanded;
			}
			else if (token[i].value[0] == '\'')
			{
				unquoted = ft_substr(token[i].value, 1,
						ft_strlen(token[i].value) - 2);
				free(token[i].value);
				token[i].value = unquoted;
			}
		}
		ft_printf("value : %s type : %d\n", token[i].value, token[i].type);
		i++;
	}
	return (0);
}
