/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/04 06:11:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include <stdlib.h>

// # define T_FUNC 0
// # define T_WORD 1
// # define T_PIPE 2
// # define T_REDIRECT_IN 3
// # define T_REDIRECT_OUT 4
// # define T_APPEND 5
// # define T_HEREDOC 6
// # define T_ENV 7
// # define T_FORBID 8
// # define T_NULL 9
// # define T_WORD_FOR_REDIRECT 10

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
	T_FORBID,
	T_NULL,
	T_WORD_FOR_REDIRECT
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
	int		code_error;
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

/****************pre parsing***********************/

int			count_tokens(char *str);
t_token		*tokenize(char *str, t_minishell *minishell);
int			count_quote(char *str);
int			check_is_forbid(char *str, int i);

/*******************tokenized**********************/
int			is_dollar(char *str, int *i, int *token_index, t_token *token);
int			is_pipe(char *str, int *i, int *token_index, t_token *token);
int			single_quote(char *str, int *i, int *token_index, t_token *token);
int			double_quote(char *str, int *i, int *token_index, t_token *token);
int			is_forbid(char *str, int *i, int *token_index, t_token *token);
int			is_redirect_in(char *str, int *i, int *token_index, t_token *token);
int			is_redirect_out(char *str, int *i, int *token_index,
				t_token *token);
int			is_special_token(char *str, int *i, int *token_index,
				t_token *token);
int			is_word(char *str, int *i, int *token_index, t_token *token);

/*******************tokenized***********************/

int			free_error(t_token *token, t_minishell *structure, int end);
char		*get_env_value(char *var_name, char **env);
// rajouter par paul
int			ft_check(t_token *tokens, int recurs, t_minishell *minishell);
int			ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell);
int			ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens);

int			ft_pipex(t_minishell *minishell);
/*********************message************************* */
int			ft_print_error(t_token *tokens, int i, int error);
int			message_error(char *first_message, char *last_message);
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
int			free_and_close(char *value1, char *value, int *save_text,
				int return_error);
void		*ft_error_free_tab(t_token *tab);
void		ft_free_error(void *value, char *text, int perrorornot,
				int exitornot);
/*****************close************** */
int			ft_close(int *fd);
void		unlink_here_doc(t_minishell *minishell);
/**********pipe********** */
int			count_pipe(t_token *tokens);

int	init_pipex(t_minishell *minishell, int count_pipe);
#endif
