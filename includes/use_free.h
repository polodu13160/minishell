/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_free.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:00:08 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 17:12:45 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USE_FREE_H
# define USE_FREE_H

# include "pipex.h"

void	free_exec(t_pip *exec);
void	free_pipex(t_minishell *minishell, int end);
void	finish_child(t_minishell *minishell, t_pip *exec, int exec_return);
int		free_all(t_token *token, t_minishell *structure, int end);
void	free_loop(t_token *token, t_minishell *minishell);
void	free_exit(t_token *token, t_minishell *minishell, t_pip *exec,
			int line_exit);
int		finish(t_pip *exec, t_minishell *minishell, int status, char *message);
void	free_token(t_token *tokens);
int		garbage_token_collector(t_token *token, int i);
int		free_and_close(char *value1, int *save_text, int return_error);
void	free_value(void *value, char *text, int perrorornot, int exitornot);

#endif