/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:13:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/04 04:21:36 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "token.h"
# include <sys/types.h>

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
int			ft_execve_next(t_minishell *minishell, t_pip *exec, int i);
void		ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i,
				int arg_exec);
int			ft_execve_first(t_minishell *minishell, t_pip *exec);

void		finish(t_pip *exec, t_minishell *minishell, int full);
int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);
int			message_error(char *first_message, char *last_message);
void		init_exec_loop(t_pip *exec);

/********************childs************************* */
int			ft_wait_child(t_minishell *minishell);
int			check_perm_infiles(t_minishell *minishell, int i, int j,
				t_pip *exec);
int			check_perm_outfiles(t_minishell *minishell, int i, int j,
				t_pip *exec);
int			ft_check_perm(t_pip *exec, t_minishell *minishell, int i);
int			ft_close_and_dup(t_pip *exec);
int			ft_close_and_dup_finish(t_pip *exec, int *new_pipe);

/************************env********************************** */

int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);
void		ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i,
				int arg_exec);

/************************error********** */
int			perr_and_rplce_exec_error(char *value, t_pip *exec);

/**************************fd_pipe*************** */
void		ft_close_pip(t_pip *exec, int *new_pipe, int substitue);
#endif