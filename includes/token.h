/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/20 03:50:53 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structures.h"

/* ************************************************************************** */
/*                            INITIALIZATION                                  */
/* ************************************************************************** */

void	main_run(t_minishell *minishell);
void	init_minishell(t_minishell *minishell);
void	isatty_run(t_minishell *minishell);
void	init_minishell_env(t_minishell *minishell, char **env, int ac,
			char **av);

/* ************************************************************************** */
/*                              TOKENIZATION                                  */
/* ************************************************************************** */

int		count_tokens(char *str);
int		tokenize(char *str, t_minishell *minishell);
int		count_quote(char *str);
void	init_data_token(t_token *token, int count);
int		check_args(char *str, t_token *token, int count);

/* ************************************************************************** */
/*                               LEXING                                       */
/* ************************************************************************** */

int		is_dollar(char *str, int *i, int *token_index, t_token *token);
int		is_pipe(char *str, int *i, int *token_index, t_token *token);
int		is_special_token(char *str, int *i, int *token_index, t_token *token);

/* ************************************************************************** */
/*                           PARSING & EXECUTION                             */
/* ************************************************************************** */

int		check(t_token *tokens, int recurs, t_minishell *minishell);
int		check_here_doc(t_token *tokens, int i, t_minishell *minishell);
int		prepare_to_pipex(t_minishell *minishell, t_token *tokens);
int		write_here_doc(int i, t_token *tokens, int save_text);
int		ft_pipex(t_minishell *minishell);

/* ************************************************************************** */
/*                          ERROR HANDLING                                    */
/* ************************************************************************** */

int		print_error(t_minishell *minishell, t_token *tokens, int i, int error);
int		message_error(char *first_message, char *last_message);

/* ************************************************************************** */
/*                        COMMAND PREPARATION                                 */
/* ************************************************************************** */

int		count_cmd(t_token *tokens, int limit_pipee);
int		join_tab_cmd(t_token *tokens, int limit_pipee, char **malloc_cmd,
			int count_pipee);
char	**store_cmd(t_token *tokens, int limit_pipee);

/* ************************************************************************** */
/*                         INPUT FILES HANDLING                              */
/* ************************************************************************** */

int		count_infiles(t_token *tokens, int limit_pipee);
int		join_tab_infiles(t_token *tokens, int limit_pipee,
			t_token *malloc_infiles, int count_pipee);
t_token	*store_infiles(t_token *tokens, int limit_pipee);

/* ************************************************************************** */
/*                        OUTPUT FILES HANDLING                              */
/* ************************************************************************** */

int		count_outfiles(t_token *tokens, int limit_pipee);
int		join_tab_outfiles(t_token *tokens, int limit_pipee,
			t_token *malloc_outfiles, int count_pipee);
t_token	*store_outfiles(t_token *tokens, int limit_pipee);

/* ************************************************************************** */
/*                          FILE DESCRIPTORS                                 */
/* ************************************************************************** */

int		ft_close(int *fd);
void	ft_close_here_doc(int i, t_minishell *minishell, t_pipe *exec,
			int error);

/* ************************************************************************** */
/*                              PIPELINES                                     */
/* ************************************************************************** */

int		count_pipee(t_token *tokens);
int		init_pipex(t_minishell *minishell, int count_pipee);

#endif
