/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:28:17 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 17:28:26 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	check_before_heredoc(t_token *tokens, int i)
{
	if (i >= 1 && tokens[i - 1].value && tokens[i - 1].type == T_HEREDOC)
		return (1);
	return (0);
}
