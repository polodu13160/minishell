/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/05/22 22:02:39 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	count_type(t_token *tokens, int type, int init, int finish)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((init == 0 && finish == 0 )|| tokens[i].value != NULL)
		if (tokens[i++].type == type)
			count++;
	while (finish != 0 || tokens[init].value != NULL)
	{
		if (tokens[init].type == T_PIPE)
			return (count);
		if (tokens[init++].type == type)
			count++;
	}
	return (count);
}

int	ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens)
{
	int i;
	i = 0;
	int var_count_pipe;
	var_count_pipe = 0;
	minishell->pipex = ft_calloc(count_type(tokens, T_PIPE, 0, 0),
			sizeof(t_pipex));
	while (var_count_pipe < count_pipe(tokens, T_PIPE, 0))
	{
		if (tokens)
	}