/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:43 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 22:43:28 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "use_free.h"
#include <libft.h>

int	perr_exec_error(char *value, t_pip *exec, int no_ambigous)
{
	if (no_ambigous == 1)
		ft_printf_fd(2, "%s: ambiguous redirect\n", value);
	else
		perror(value);
	exec->error = 1;
	return (1);
}

int	count_pipe(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == T_PIPE)
			count++;
		i++;
	}
	return (count);
}

void	init_exec_loop(t_pip *exec)
{
	exec->error = 0;
	exec->fd_infile.value = NULL;
	exec->fd_infile.type = T_NULL;
	exec->fd_outfile.type = T_NULL;
	exec->fd_outfile.value = NULL;
	exec->fd_infile.fd = -1;
	exec->fd_outfile.fd = -1;
}
