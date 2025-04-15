/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:32:05 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/15 19:42:16 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "new_libft/ressource/libft.h"
# include <stdlib.h>

# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT_IN 3
# define T_REDIRECT_OUT 4
# define T_APPEND 5
# define T_HEREDOC 6
# define T_SEMICOLON 7
# define T_DOUBLE_QUOTE 8
# define T_SINGLE_QUOTE 9
# define T_ENV 10
# define T_AND 11
# define T_OR 12
# define T_SPACE 13
# define T_STRING 14

typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

int			count_tokens(char *str);
t_token		*tokenize(char *str);

#endif
