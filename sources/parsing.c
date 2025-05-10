/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:24 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/10 16:28:59 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
				token[i].value = check_quote_command(token[i].value);
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
		, || or && or ; or () or \\ \n",
							2);
			return (1);
		}
		else if (token[i].type == T_WORD)
		{
		}
		ft_printf("value : %s type : %d\n", token[i].value, token[i].type);
		i++;
	}
	return (0);
}
