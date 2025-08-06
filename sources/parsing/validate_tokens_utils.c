/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:28:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 15:24:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "token.h"

int	before_is_heredoc(t_token *tokens, int i)
{
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		return (1);
	return (0);
}

int	before_is_ambigous(t_token *tokens, int i)
{
	if (i >= 1 && tokens[i - 1].value && (tokens[i - 1].type == T_APPEND
			|| tokens[i - 1].type == T_REDIRECT_IN || tokens[i
			- 1].type == T_REDIRECT_OUT))
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
