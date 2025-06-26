/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:58:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/26 17:47:45 by antbonin         ###   ########.fr       */
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

int		check_parsing(t_token *token, t_minishell *minishell, int ret, int i);
char	*get_env_value(char *var_name, char **env);
char	*return_env(char *str, t_minishell *minishell);
char	*check_quote_command(char *str);
char	*parse_single_quotes(char *str);
char	*parse_quotes(char *str, t_minishell *minishell);
char	*handle_double_quotes_env(char *str);
char	*handle_single_quotes_env(char *str);
char	*parse_env(char *str, t_minishell *minishell);
int		process_dollar(t_token *token, t_minishell *minishell, int type, int i);
void	process_env_var(char *str, char *result, t_index *index,
			t_minishell *minishell);

/**********************************************************/

void	minishell_env(t_minishell *minishell, char **env, int ac, char **av);
void	init_minishell(t_minishell *minishell);

#endif