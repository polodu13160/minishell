/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/09/03 15:19:13 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define GREENBOLD "\001\e[1;32m\002"
# define RESET "\001\e[0m\002"

# include "signal.h"
# include "structures.h"

/* ************************************************************************** */
/*                            GLOBAL VARIABLES                               */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_sig;

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_cd
{
	char						*new_var;
	char						**new_env;
	int							name_len;
	int							error;
	int							var_index;
}								t_cd;

/* ************************************************************************** */
/*                            SIGNAL HANDLING                                */
/* ************************************************************************** */

void							setup_signals(void);
void							setup_signals_child(void);
void							handle_sigint_child(int signal);
void							handle_sigint_heredoc(int signal);
void							setup_signals_heredoc(void);
int								check_sig(int statuetemp);
int								check_interrupt(void);
void							check_sig_main(t_minishell *minishell);

/* ************************************************************************** */
/*                           BUILTIN EXECUTION                               */
/* ************************************************************************** */

int								apply_builtins(t_minishell *minishell, int i,
									t_pipe *exec, int print_exit);
int								check_builtins(t_minishell *minishell, int i);

/* ************************************************************************** */
/*                        ENVIRONMENT MANAGEMENT                             */
/* ************************************************************************** */

char							**copy_original_env(char **env);
int								ft_env(t_minishell *minishell, int pwd);
int								env_loop(char **copy_env, char **env, int *i);
char							**declare_env(void);
char							*get_env_value(char *var_name,
									t_minishell *minishell);

/* ************************************************************************** */
/*                            EXPORT BUILTIN                                 */
/* ************************************************************************** */

int								ft_export(char **str, t_minishell *minishell);
int								ft_unset(char **str, t_minishell *minishell,
									int i);
int								check_double(char *str, t_minishell *minishell,
									int j, int name_len);
int								copy_env_loop(char **new_env, char **str,
									t_minishell *minishell, int i);
int								is_valid_identifier(char *str);
int								print_export(t_minishell *minishell);
int								ft_strcmp_whithout_equality(char *env,
									char *str);
int								handle_invalid_identifier(char *var_name);

/* ************************************************************************** */
/*                             ECHO BUILTIN                                  */
/* ************************************************************************** */

int								ft_echo(char **str);

/* ************************************************************************** */
/*                              CD BUILTIN                                   */
/* ************************************************************************** */

int								ft_cd(char **str, t_minishell *minishell,
									int error, int return_func_check_path);
int								copy_new_env(t_minishell *minishell,
									char *new_var);
int								check_var_exist(t_minishell *minishell,
									const char *name, int name_len);
int								replace_existing_var(t_minishell *minishell,
									char *new_var, int var_index);
void							declare_putenv(t_cd *cd, const char *name);
int								check_path(char *str);

/* ************************************************************************** */
/*                             EXIT BUILTIN                                  */
/* ************************************************************************** */

int								ft_exit(char **str, t_minishell *minishell,
									t_pipe *exec, int print_exit);

/* ************************************************************************** */
/*                          UTILITY FUNCTIONS                                */
/* ************************************************************************** */

void							shift_token(t_token *token, int i);
int								validate_parsing(t_token *token,
									t_minishell *minishell, int i);
void							check_expand_special(t_token *tokens);

#endif