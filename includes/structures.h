/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:59:09 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/07 23:09:48 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdio.h>
# include <sys/types.h>

typedef struct s_token
{
	char		*value;
	int			index;
	int			type;
	int			fd;
}				t_token;

typedef struct s_pip
{
	t_token		fd_infile;
	t_token		fd_outfile;
	int			pipe[2];
	char		**path_args;
	char		*path_absolut_exec;
	int			error;
	char		**env;
}				t_pipe;

typedef enum e_token_type
{
	T_FUNC,
	T_WORD,
	t_pipeE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_ENV,
	T_AMBIGOUS,
	T_NULL,
	T_WORD_FOR_REDIRECT,
	T_IGNORE
}				t_token_type;

typedef struct s_pipex
{
	int			init;
	t_token		*infiles;
	t_token		*outfiles;
	char		**cmd;
}				t_pipeex;

typedef struct s_minishell
{
	char		*cwd;
	pid_t		*pids;
	t_token		*tokens;
	char		*cwd_join;
	char		*line;
	char		**env;
	int			count_pipee;
	t_pipeex	*pipex;
	int			return_command;
}				t_minishell;

typedef struct s_parse_data
{
	int			in_dquote;
	int			in_squote;
	int			*error;
	int			token_index;
	int			start;
	int			i;
}				t_parse_data;

#endif