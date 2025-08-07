/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_ambigous.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:09:37 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/07 22:31:41 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdlib.h"
#include "libft.h"

int	declare_ambigous(t_token *token, t_minishell *minishell)
{
	char	*temp;
	char	*old_token;

	old_token = ft_strdup(token->value);
	if (!old_token)
		return (1);
	temp = expand_environment_vars(token->value, minishell);
	if (!temp)
	{
		free(old_token);
		return (1);
	}
	free(token->value);
	token->value = temp;
	if (ft_strncmp(token->value, "", 2) == 0 || is_ambigous(token->value))
	{
		free(token->value);
		token->type = T_AMBIGOUS;
		token->value = old_token;
		return (1);
	}
	free(old_token);
	return (0);
}
