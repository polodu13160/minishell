/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:13:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/09/10 15:29:29 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structures.h"

int		check_perm(t_pipe *exec, t_minishell *minishell, int i);
int		ft_close(int *fd);
int		execve_next(t_minishell *minishell, t_pipe *exec, int i,
			int return_exec);
int		exec_to_env(t_minishell *minishell, t_pipe *exec, int i, int arg_exec);
int		execve_first(t_minishell *minishell, t_pipe *exec);
int		add_slash_to_env(t_pipe *exec);
int		set_path_env(t_pipe *exec, char **env);

int		add_slash_to_env(t_pipe *exec);
int		set_path_env(t_pipe *exec, char **env);
int		perr_exec_error(char *value, t_pipe *exec, int no_ambigous);

int		check_perm_infiles(t_minishell *minishell, int i, int j, t_pipe *exec);
int		check_perm_outfiles(t_minishell *minishell, int i, int j, t_pipe *exec);
int		check_perm(t_pipe *exec, t_minishell *minishell, int i);
int		close_and_dup(t_pipe *exec);
int		close_and_dup_last(t_pipe *exec, int *new_pipe);
void	init_exec_loop(t_pipe *exec);
void	close_pip(t_pipe *exec, int *new_pipe, int substitue);
int		execve_builtin_no_child(t_minishell *minishell, t_pipe *exec,
			int dup_redirect_in, int dup_redirect_out);
int		execve_builtin_first(t_minishell *minishell, t_pipe *exec);
int		execve_builtin_next(t_minishell *minishell, t_pipe *exec, int i,
			int return_exec);
int		wait_child(t_minishell *minishell, int status, int pid, int coredumped);
void	error_fork_or_pipe(t_pipe *exec, t_minishell *minishell, int *new_pipe,
			int ifpipe);
void	close_2_fds(int *fd, int *fd2);
int		check_acces_outfiles(t_minishell *minishell, int i, int j,
			t_pipe *exec);
int		error_dup2_execve_builtin_no_child(t_pipe *exec, int dup_redirect_in,
			int dup_redirect_out);
int		is_only_space_or_point(char *str);
int		dup_infile_and_outfile_builtin_no_child(t_pipe *exec,
			int dup_redirect_in, int dup_redirect_out);
int		if_is_only_space_or_point(t_minishell *minishell, int i);
int		message_error_output(t_minishell *minishell, t_pipe *exec,
			int value_return, char *cmd);
void	cleanup_here_doc_rl_clear_hist_and_reset_signal(t_minishell *minishell,
			t_pipe exec, int index);

#endif
