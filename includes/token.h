/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:18 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
#include "sys/types.h"
#include "structures.h"

/* ************************************************************************** */
/*                            INITIALIZATION                                  */
/* ************************************************************************** */

void		main_run(t_minishell *minishell);
void		init_minishell(t_minishell *minishell);
void		isatty_run(t_minishell *minishell);
void		init_minishell_env(t_minishell *minishell, char **env, int ac,
				char **av);

/* ************************************************************************** */
/*                              TOKENIZATION                                  */
/* ************************************************************************** */

int			count_tokens(char *str);
int			tokenize(char *str, t_minishell *minishell);
int			count_quote(char *str);
void		init_data_token(t_token *token, int count);
int			check_args(char *str, t_token *token, int count);

/* ************************************************************************** */
/*                               LEXING                                       */
/* ************************************************************************** */

int			is_dollar(char *str, int *i, int *token_index, t_token *token);
int			is_pipe(char *str, int *i, int *token_index, t_token *token);
int			is_special_token(char *str, int *i, int *token_index,
				t_token *token);

/* ************************************************************************** */
/*                           PARSING & EXECUTION                             */
/* ************************************************************************** */

int			check(t_token *tokens, int recurs, t_minishell *minishell);
int			check_here_doc(t_token *tokens, int i, t_minishell *minishell);
int			prepare_to_pipex(t_minishell *minishell, t_token *tokens);
int			write_here_doc(int i, t_token *tokens, int save_text);
int			ft_pipex(t_minishell *minishell);

/* ************************************************************************** */
/*                          ERROR HANDLING                                    */
/* ************************************************************************** */

int			print_error(t_minishell *minishell,t_token *tokens, int i, int error);
int			message_error(char *first_message, char *last_message);
int			message_output_no_child(int statuetemp, t_minishell *minishell, t_pip *exec);

/* ************************************************************************** */
/*                        COMMAND PREPARATION                                 */
/* ************************************************************************** */

int			count_cmd(t_token *tokens, int limit_pipe);
int			join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
				int count_pipe);
char		**store_cmd(t_token *tokens, int limit_pipe);

/* ************************************************************************** */
/*                         INPUT FILES HANDLING                              */
/* ************************************************************************** */

int			count_infiles(t_token *tokens, int limit_pipe);
int			join_tab_infiles(t_token *tokens, int limit_pipe,
				t_token *malloc_infiles, int count_pipe);
t_token		*store_infiles(t_token *tokens, int limit_pipe);

/* ************************************************************************** */
/*                        OUTPUT FILES HANDLING                              */
/* ************************************************************************** */

int			count_outfiles(t_token *tokens, int limit_pipe);
int			join_tab_outfiles(t_token *tokens, int limit_pipe,
				t_token *malloc_outfiles, int count_pipe);
t_token		*store_outfiles(t_token *tokens, int limit_pipe);


/* ************************************************************************** */
/*                          FILE DESCRIPTORS                                 */
/* ************************************************************************** */

int			ft_close(int *fd);

/* ************************************************************************** */
/*                              PIPELINES                                     */
/* ************************************************************************** */

int			count_pipe(t_token *tokens);
int			init_pipex(t_minishell *minishell, int count_pipe);

#endif
