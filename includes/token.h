/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/19 12:50:17 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include <stdlib.h>

# define T_FUNC 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT_IN 3
# define T_REDIRECT_OUT 4
# define T_APPEND 5
# define T_HEREDOC 6
# define T_ENV 7
# define T_FORBID 8
# define T_NULL 9

typedef struct s_minishell
{
	int nb_here_doc;
	char	*cwd;
	char	*cwd_join;
	char	*line;
	char	**env;
	int		code_error;
}			t_minishell;

typedef struct s_token
{
	char	*value;
	int		type;
	char	**option;
	char	*new_value;
}			t_token;



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

int					free_error(t_token *token, t_minishell *structure, int end);

//rajouter par paul 
int	ft_check(t_token *tokens, int recurs, t_minishell *minishell);
int ft_check_here_doc(t_token *tokens, int i, t_minishell *minishell);

#endif
