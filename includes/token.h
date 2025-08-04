/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 22:24:44 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
#include "sys/types.h"

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef enum e_token_type
{
	T_FUNC,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_ENV,
	T_NULL,
	T_WORD_FOR_REDIRECT,
	T_IGNORE
}			t_token_type;

typedef struct s_token
{
	char	*value;
	int		type;
	char	**option;
	int		fd;
}			t_token;

typedef struct s_pipex
{
	int		init;
	t_token	*infiles;
	t_token	*outfiles;
	char	**cmd;
}			t_pipex;

typedef struct s_minishell
{
	char	*cwd;
	pid_t	*pids;
	t_token	*tokens;
	char	*cwd_join;
	char	*line;
	char	**env;
	int		count_pipe;
	t_pipex	*pipex;
	int		return_command;
}			t_minishell;

typedef struct s_parse_data
{
	int		in_dquote;
	int		in_squote;
	int		*error;
	int		token_index;
	int		start;
	int		i;
}			t_parse_data;

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

int			print_error(t_token *tokens, int i, int error);
int			message_error(char *first_message, char *last_message);
int			message_output_no_child(int statuetemp, t_minishell *minishell);

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
/*                           MEMORY MANAGEMENT                                */
/* ************************************************************************** */

int			free_and_close(char *value1, int *save_text, int return_error);
void		free_value(void *value, char *text, int perrorornot,
				int exitornot);

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
