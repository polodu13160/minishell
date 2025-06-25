/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/26 00:01:10 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
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

int								apply_builtins(t_minishell *minishell, int i,
									t_pip *exec);
int								check_builtins(t_minishell *minishell, int i);

char							**copy_original_env(char **env);
void							shift_token(t_token *token, int i);
int								check_token(t_token *token,
									t_minishell *minishell);
void							check_expand_special(t_token *tokens);
int								ft_env(t_minishell *minishell, int pwd);
int								env_loop(char **copy_env, char **env, int *i);
char							**declare_env(void);

/*****************************export****************************************/

int								ft_export(char **str, t_minishell *minishell,
									int i);
int								ft_unset(char **str, t_minishell *minishell,
									int i);

/*******************************echo****************************************/

int								ft_echo(char **str, int i);

/********************************cd*****************************************/

int								ft_cd(char **str, int i,
									t_minishell *minishell);
char							*ft_strjoin3(const char *s1, const char *s2,
									const char *s3);
int								copy_new_env(t_minishell *minishell,
									char *new_var);
int								check_var_exist(t_minishell *minishell,
									const char *name, int name_len);
int								replace_existing_var(t_minishell *minishell,
									char *new_var, int var_index);
void							declare_putenv(t_cd *cd, const char *name);

/*********************************exit***************************************/

void							ft_exit(char **str, t_minishell *minishell,
									int i, t_pip *exec);
void							free_exit(t_token *token,
									t_minishell *minishell, t_pip *exit);

/****************************************************************************/

int								free_all(t_token *token, t_minishell *minishell,
									int end);

#endif