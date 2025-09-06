/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_free.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:00:08 by pde-petr          #+#    #+#             */
/*   Updated: 2025/09/06 15:43:20 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USE_FREE_H
# define USE_FREE_H

# include "pipex.h"

void	free_exec(t_pipe *exec);
void	free_pipex(t_minishell *minishell, int end, int i);
void	finish_child(t_minishell *minishell, t_pipe *exec, int exec_return);
int		free_all(t_token *token, t_minishell *structure, int end);
void	free_env(t_minishell *minishell);
void	free_loop(t_token *token, t_minishell *minishell);
void	free_exit(t_token *token, t_minishell *minishell, t_pipe *exec,
			int line_exit);
int		finish(t_pipe *exec, t_minishell *minishell, int status, char *message);
void	free_token(t_token *tokens);
int		free_tokens_parsing(t_token *token, int i);
int		free_and_close(char *value1, int *save_text, int return_error);
void	free_value(void *value, char *text, int perrorornot, int exitornot);

#endif