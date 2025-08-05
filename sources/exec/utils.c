/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:43 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 02:45:20 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "use_free.h"
#include <libft.h>

void	error_fork_or_pipe(t_pip *exec, t_minishell *minishell, int *new_pipe,
		int ifpipe)
{
	wait_child(minishell);
	if (exec->fd_infile.value != NULL && exec->fd_infile.type != T_PIPE)
		ft_close(&exec->fd_infile.fd);
	if (exec->fd_outfile.type != T_PIPE && exec->fd_outfile.value != NULL)
		ft_close(&exec->fd_outfile.fd);
	if (ifpipe)
		ft_printf_fd(2, "Error Pipe\n");
	else
		ft_printf_fd(2, "Error Fork\n");
	close_pip(exec, new_pipe, 0);
	if (ifpipe)
		finish_child(minishell, exec, 10);
	finish_child(minishell, exec, 1);
	
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
