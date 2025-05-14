/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:58:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/12 15:07:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "token.h"

typedef struct s_index
{
	int	i;
	int	j;
}		t_index;

typedef struct s_quote_state
{
	int	in_dquote;
	int	in_squote;
}		t_quote_state;

/*************************Parsing*************************/

int		check_parsing(t_token *token, t_minishell minishell);
char	*get_env_value(char *var_name, char **env);
char	*return_env(char *str, t_minishell minishell);
char	*check_quote_command(char *str);
int		check_parsing(t_token *token, t_minishell minishell);
char	*parse_single_quotes(char *str);
char	*parse_quotes(char *str, t_minishell minishell);
char	*handle_double_quotes_env(char *str);
char	*handle_single_quotes_env(char *str);

/*********************************************************/

#endif