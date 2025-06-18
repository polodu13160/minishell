/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:00:08 by pde-petr          #+#    #+#             */
/*   Updated: 2025/06/17 21:01:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_exec(t_pip *exec);
void	ft_free_env(t_minishell *minishell);
void	ft_free_tokens(t_minishell *minishell);
void	free_pipex(t_minishell *minishell, int end);
void	ft_finish_child(t_minishell *minishell, t_pip *exec);
int		free_all(t_token *token, t_minishell *structure, int end);
void	free_loop(t_token *token, t_minishell *minishell);
void	free_exit(t_token *token, t_minishell *minishell, t_pip *exec);
