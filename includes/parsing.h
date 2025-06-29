/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:58:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/29 18:39:33 by antbonin         ###   ########.fr       */
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

typedef struct s_retokenize_data
{
	int	old_count;
	int	nb_new;
	int	insert_pos;
}		t_retokenize_data;

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
int		process_env_var(char *str, char *result, t_index *index,
			t_minishell *minishell);
int		retokenize(t_token *tokens, t_minishell *minishell, int i);
void	process_quote_character(char *str, char *copy, t_quote_state *state,
			t_index *index);
void	handle_double_quote(int *i, int *inside_dquotes, int inside_squotes);
void	handle_single_quote(int *i, int *inside_squotes, int inside_dquotes);
char	*allocate_quote_copy(char *str);
char	*prepare_string_for_quote_check(char *str);
int		parse_quote_loop(char *str, t_minishell *minishell, t_index *index,
			char *result);
char	*handle_double_quotes_env(char *str);
char	*handle_single_quotes_env(char *str);
void	copy_single(char *str, char *result, int *i, int *j);
char	*ft_join_malloc(char *malloc_str1, char *malloc_str2);
char	*ft_chardup(char c);
char	*extract_var_env(char *str);

/*********************************retokenize*******************/

t_token	*tokenize_expanded_value(char *expanded_value);
void	copy_tokens_after(t_token *result, t_token *tokens, int i,
			t_retokenize_data *data);
void	copy_new_tokens(t_token *result, t_token *new_tokens, int start,
			int nb_new);
void	copy_tokens_before(t_token *result, t_token *tokens, int i);
int		count_tokens_array(t_token *tokens);
int		count_new_tokens(t_token *new_tokens);

/**********************************************************/

char	**split_token_value(char *value, int *nb_new);

void	minishell_env(t_minishell *minishell, char **env, int ac, char **av);
void	init_minishell(t_minishell *minishell);

#endif