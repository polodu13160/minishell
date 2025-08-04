/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:58:31 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/04 16:38:12 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "token.h"

typedef struct s_index
{
	int			i;
	int			j;
}				t_index;

typedef struct s_quote_state
{
	int			in_dquote;
	int			in_squote;
}				t_quote_state;

typedef struct s_retokenize_data
{
	int			old_count;
	int			nb_new;
	int			insert_pos;
}				t_retokenize_data;

typedef struct s_expand_data
{
	int			i;
	int			j;
	int			in_dquote;
	int			in_squote;
	t_minishell	*minishell;
}				t_expand_data;

/*************************Parsing*************************/

int				check_token(t_token *token, t_minishell *minishell, int ret,
					int i);
char			*return_env(char *str, t_minishell *minishell);
char			*check_quote_command(char *str);
char			*parse_single_quotes(char *str);
char			*parse_quotes(char *str, t_minishell *minishell);
char			*parse_env(char *str, t_minishell *minishell, int is_in_double);
int				process_dollar(t_token *token, t_minishell *minishell, int i);
int				process_env_var(char *str, char *result, t_index *index,
					t_minishell *minishell);
int				retokenize(t_token *tokens, t_minishell *minishell, int i);
void			process_quote_character(char *str, char *copy,
					t_quote_state *state, t_index *index);
void			handle_double_quote(int *i, int *inside_dquotes,
					int inside_squotes);
void			handle_single_quote(int *i, int *inside_squotes,
					int inside_dquotes);
void			shift_token(t_token *token, int i);
char			*allocate_quote_copy(char *str);
char			*prepare_string_for_quote_check(char *str);
int				parse_quote_loop(char *str, t_minishell *minishell,
					t_index *index, char *result);
char			*parse_env_loop(char *str, t_minishell *minishell, char *result,
					int is_in_double);
char			*handle_double_quotes_env(char *str, int i, int j);
char			*handle_single_quotes_env(char *str, int i, int j,
					char *result);
char			*parse_mixed_quotes(char *str, t_minishell *minishell);
void			handle_special_var(char *str, char *result,
					t_expand_data *data);
void			append_value_to_result(char *result, char *value, int *j);
void			copy_single(char *str, char *result, int *i, int *j);
char			*ft_join_malloc(char *malloc_str1, char *malloc_str2);
char			*ft_chardup(char c);
char			*extract_var_env(char *str);
char			*extract_var_name(char *str, int *i, int *var_len);
size_t			calculate_needed_size(char *str, t_minishell *minishell, int i,
					size_t total_size);
char			*copy_return_command(t_minishell *minishell, char *var_name);

/*********************************retokenize*******************/

t_token			*tokenize_expanded_value(char *expanded_value);
void			copy_tokens_after(t_token *result, t_token *tokens, int i,
					t_retokenize_data *data);
void			copy_new_tokens(t_token *result, t_token *new_tokens, int start,
					int nb_new);
void			copy_tokens_before(t_token *result, t_token *tokens, int i);
int				count_tokens_array(t_token *tokens);
int				count_new_tokens(t_token *new_tokens);

/**********************************************************/


#endif