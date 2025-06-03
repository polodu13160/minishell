/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:13:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/03 01:38:13 by pde-petr         ###   ########.fr       */
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
int			ft_exec(t_minishell *minishell, t_pip *exec, int i);
void		ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i,
				int arg_exec);
void		message_output(int statuetemp, t_minishell *minishell,
				pid_t pidvalue);
int			message_error(char *first_message, char *last_message);
int			ft_execve_first(t_minishell *minishell, t_pip *exec);
int			ft_execve_last(int *fd, t_pip *exec);
void		free_tab_three_dim(char ***tab);
void		free_tab_two_dim(char **tab);

void		finish(t_pip *exec, t_minishell *minishell, int full);
int			ft_add_slash_to_env(t_pip *exec);
int			ft_set_path_env(t_pip *exec, char **env);
int			message_error(char *first_message, char *last_message);
int			ft_execve_middle(int *fd, t_pip *exec, int exec_args, int *new_fd);
int			ft_execve_last_parent(pid_t pid, t_pip *exec, int *fd);
#endif