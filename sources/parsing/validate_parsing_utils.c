/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parsing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:12:55 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 15:16:50 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdlib.h"

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

void	get_token_index(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		tokens[i].index = i;
		i++;
	}
}
