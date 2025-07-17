/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/17 02:27:38 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "libft.h"
# include "pipex.h"
# include "signal.h"
# include "token.h"
# include <stdlib.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig;

typedef struct s_cd
{
	char						*new_var;
	char						**new_env;
	int							name_len;
	int							error;
	int							var_index;
}								t_cd;

void							setup_signals(void);
void							setup_signals_child(void);
void							handle_sigint_child(int signal);
void							setup_signals_heredoc(void);
void							check_sig(int statuetemp);

int								in_process_marker(void);

int								apply_builtins(t_minishell *minishell, int i,
									t_pip *exec, int print_exit);
int								check_builtins(t_minishell *minishell, int i);

char							**copy_original_env(char **env);
void							shift_token(t_token *token, int i);
int								check_token(t_token *token,
									t_minishell *minishell, int i);
void							check_expand_special(t_token *tokens);
int								ft_env(t_minishell *minishell, int pwd);
int								env_loop(char **copy_env, char **env, int *i);
char							**declare_env(void);
char							*get_env_value(char *var_name, char **env);

/*****************************export****************************************/

int								ft_export(char **str, t_minishell *minishell,
									int i);
int								ft_unset(char **str, t_minishell *minishell,
									int i);
int								check_double(char **str, t_minishell *minishell,
									char *var_name, int i);
char							**copy_env(t_minishell *minishell, char **str,
									int i);
int								is_valid_identifier(char *str);
int								print_export(t_minishell *minishell);

/*******************************echo****************************************/

int								ft_echo(char **str);

/********************************cd*****************************************/

int								ft_cd(char **str, t_minishell *minishell,
									int error);
char							*ft_strjoin3(const char *s1, const char *s2,
									const char *s3);
int								copy_new_env(t_minishell *minishell,
									char *new_var);
int								check_var_exist(t_minishell *minishell,
									const char *name, int name_len);
int								replace_existing_var(t_minishell *minishell,
									char *new_var, int var_index);
void							declare_putenv(t_cd *cd, const char *name);
int								check_path(char *str);

/*********************************exit***************************************/

int								ft_exit(char **str, t_minishell *minishell,
									t_pip *exec, int print_exit);

/****************************************************************************/

int								free_all(t_token *token, t_minishell *minishell,
									int end);

#endif