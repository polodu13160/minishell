/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_dup_fork_pipe_childs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:35:09 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "use_free.h"

void	error_fork_or_pipe(t_pipe *exec, t_minishell *minishell, int *new_pipe,
		int ifpipe)
{
	wait_child(minishell, 0, 0);
	if (exec->fd_infile.value != NULL && exec->fd_infile.type != t_pipeE)
		ft_close(&exec->fd_infile.fd);
	if (exec->fd_outfile.type != t_pipeE && exec->fd_outfile.value != NULL)
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
