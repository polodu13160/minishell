/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/18 18:26:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "new_libft/ressource/libft.h"
# include <stdlib.h>

# define T_FUNC 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT_IN 3
# define T_REDIRECT_OUT 4
# define T_APPEND 5
# define T_HEREDOC 6
# define T_SEMICOLON 7
# define T_ENV 8
# define T_AND 9

typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

int			count_tokens(char *str);
t_token		*tokenize(char *str);

/*******************tokenized**********************/
int			is_semicolon(char *str, int *i, int *token_index, t_token *token);
int			is_dollar(char *str, int *i, int *token_index, t_token *token);
int			is_pipe(char *str, int *i, int *token_index, t_token *token);
int			single_quote(char *str, int *i, int *token_index, t_token *token);
int			double_quote(char *str, int *i, int *token_index, t_token *token);
int			is_and(char *str, int *i, int *token_index, t_token *token);
int			is_redirect_in(char *str, int *i, int *token_index, t_token *token);
int			is_redirect_out(char *str, int *i, int *token_index,
				t_token *token);
/*******************tokenized**********************/

#endif
