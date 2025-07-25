/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:00:08 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/01 16:04:04 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "pipex.h"

void	ft_free_exec(t_pip *exec);
void	ft_free_env(t_minishell *minishell);
void	free_pipex(t_minishell *minishell, int end);
void	ft_finish_child(t_minishell *minishell, t_pip *exec, int exec_return);
int		free_all(t_token *token, t_minishell *structure, int end);
void	free_loop(t_token *token, t_minishell *minishell);
void	free_exit(t_token *token, t_minishell *minishell, t_pip *exec,
			int line_exit);
int		ft_finish(t_pip *exec, t_minishell *minishell, int status);
void	free_token(t_token *tokens);
int		garbage_token_collector(t_token *token, int i);

#endif