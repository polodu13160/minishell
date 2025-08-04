/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 17:09:16 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
#include "sys/types.h"


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
	int		nb_here_doc;
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

/*********************************main************************************ */

void		main_run(t_minishell *minishell);
void		init_minishell(t_minishell *minishell);
void		isatty_run(t_minishell *minishell);
void		init_minishell_env(t_minishell *minishell, char **env, int ac,
				char **av);

/*****************************pre parsing**************************************/

int			count_tokens(char *str);
int			tokenize(char *str, t_minishell *minishell);
int			count_quote(char *str);
int			check_is_forbid(char *str, int i);
void		init_data_null(t_token *token, int count);
int			check_args(char *str, t_token *token, int count);

/********************************lexing**************************************/

int			is_dollar(char *str, int *i, int *token_index, t_token *token);
int			is_pipe(char *str, int *i, int *token_index, t_token *token);
int			single_quote(char *str, int *i, int *token_index, t_token *token);
int			double_quote(char *str, int *i, int *token_index, t_token *token);

int			is_redirect_in(char *str, int *i, int *token_index, t_token *token);
int			is_redirect_out(char *str, int *i, int *token_index,
				t_token *token);
int			is_special_token(char *str, int *i, int *token_index,
				t_token *token);
int			is_word(char *str, int *i, int *token_index, t_token *token);

/*************************************************************************/

int			free_all(t_token *token, t_minishell *structure, int end);
int			ft_check(t_token *tokens, int recurs, t_minishell *minishell);
int			ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell);
int			ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens);
int			write_here_doc(int i, t_token *tokens, int save_text);
int			ft_pipex(t_minishell *minishell);

/*********************message************************* */

int			ft_print_error(t_token *tokens, int i, int error);
int			message_error(char *first_message, char *last_message);
int			message_output_no_child(int statuetemp, t_minishell *minishell);

/**********************prepare cmd************** */

int			ft_count_cmd(t_token *tokens, int limit_pipe);
int			ft_join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
				int count_pipe);
char		**ft_store_cmd(t_token *tokens, int limit_pipe);

/************************prepare infile***************** */

int			ft_count_infiles(t_token *tokens, int limit_pipe);
int			ft_join_tab_infiles(t_token *tokens, int limit_pipe,
				t_token *malloc_infiles, int count_pipe);
t_token		*ft_store_infiles(t_token *tokens, int limit_pipe);

/**********************prepare outfile******************** */

int			ft_count_outfiles(t_token *tokens, int limit_pipe);
int			ft_join_tab_outfiles(t_token *tokens, int limit_pipe,
				t_token *malloc_outfiles, int count_pipe);
t_token		*ft_store_outfiles(t_token *tokens, int limit_pipe);

/********************free********************* */

int			free_and_close(char *value1, int *save_text, int return_error);
void		*ft_error_free_tab(t_token *tab);
void		ft_free_all(void *value, char *text, int perrorornot,
				int exitornot);

/*****************close************** */

int			ft_close(int *fd);
void		unlink_here_doc(t_minishell *minishell);

/**********pipe********** */
int			count_pipe(t_token *tokens);

int			init_pipex(t_minishell *minishell, int count_pipe);
#endif
