/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:13:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 19:34:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structures.h"

int		check_perm(t_pip *exec, t_minishell *minishell, int i);
int		ft_close(int *fd);
int		execve_next(t_minishell *minishell, t_pip *exec, int i,
			int return_exec);
int		exec_to_env(t_minishell *minishell, t_pip *exec, int i, int arg_exec);
int		execve_first(t_minishell *minishell, t_pip *exec);
int		add_slash_to_env(t_pip *exec);
int		set_path_env(t_pip *exec, char **env);

int		add_slash_to_env(t_pip *exec);
int		set_path_env(t_pip *exec, char **env);
void	message_output(int statuetemp, t_minishell *minishell, pid_t pidvalue);
int		perr_exec_error(char *value, t_pip *exec);
void	free_pipex(t_minishell *structure, int end);

int		check_perm_infiles(t_minishell *minishell, int i, int j, t_pip *exec);
int		check_perm_outfiles(t_minishell *minishell, int i, int j, t_pip *exec);
int		check_perm(t_pip *exec, t_minishell *minishell, int i);
int		close_and_dup(t_pip *exec);
int		close_and_dup_last(t_pip *exec, int *new_pipe);
void	init_exec_loop(t_pip *exec);
void	close_pip(t_pip *exec, int *new_pipe, int substitue);
int		execve_builtin_no_child(t_minishell *minishell, t_pip *exec,
			int dup_redirect_in, int dup_redirect_out);
int		execve_builtin_first(t_minishell *minishell, t_pip *exec);
int		execve_builtin_next(t_minishell *minishell, t_pip *exec, int i,
			int return_exec);
int		wait_child(t_minishell *minishell);
void	error_fork_or_pipe(t_pip *exec, t_minishell *minishell, int *new_pipe,
			int ifpipe);
void	close_2_fds(int *fd, int *fd2);
int		check_acces_outfiles(t_minishell *minishell, int i, int j, t_pip *exec);
int		error_dup2_execve_builtin_no_child(t_pip *exec, int dup_redirect_in,
			int dup_redirect_out);
int		is_only_space_or_point(char *str);
int		dup_infile_and_outfile_builtin_no_child(t_pip *exec,
			int dup_redirect_in, int dup_redirect_out);

#endif
