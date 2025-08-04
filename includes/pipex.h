/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:13:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/04 16:22:08 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "token.h"

typedef struct s_pip
{
	t_token	fd_infile;
	t_token	fd_outfile;
	int		pipe[2];
	char	**path_args;
	char	*path_absolut_exec;
	int		error;
	char	**env;
}			t_pip;

int			ft_check_perm(t_pip *exec, t_minishell *minishell, int i);
int			ft_close(int *fd);
int			ft_execve_next(t_minishell *minishell, t_pip *exec, int i,
				int return_exec);
int			ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i,
				int arg_exec);
int			ft_execve_first(t_minishell *minishell, t_pip *exec);
int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);

int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);
void		ft_message_output(int statuetemp, t_minishell *minishell,
				pid_t pidvalue);
int			ft_perr_exec_error(char *value, t_pip *exec);
void		free_pipex(t_minishell *structure, int end);
int			free_all(t_token *token, t_minishell *structure, int end);
int			ft_check_perm_infiles(t_minishell *minishell, int i, int j,
				t_pip *exec);
int			ft_check_perm_outfiles(t_minishell *minishell, int i, int j,
				t_pip *exec);
int			ft_check_perm(t_pip *exec, t_minishell *minishell, int i);
int			ft_close_and_dup(t_pip *exec);
int			ft_close_and_dup_last(t_pip *exec, int *new_pipe);
void		ft_init_exec_loop(t_pip *exec);
void		ft_close_pip(t_pip *exec, int *new_pipe, int substitue);
int			ft_execve_builtin_no_child(t_minishell *minishell, t_pip *exec,
				int dup_redirect_in, int dup_redirect_out);
int			ft_execve_builtin_first(t_minishell *minishell, t_pip *exec);
int			ft_execve_builtin_next(t_minishell *minishell, t_pip *exec, int i,
				int return_exec);
int			ft_wait_child(t_minishell *minishell);
void		error_fork_or_pipe(t_pip *exec, t_minishell *minishell,
				int *new_pipe, int ifpipe);
void		ft_close_2_fds(int *fd, int *fd2);
int			ft_check_acces_outfiles(t_minishell *minishell, int i, int j,
				t_pip *exec);

#endif
