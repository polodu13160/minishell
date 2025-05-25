/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/25 16:39:25 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "libft.h"
# include "token.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cd
{
	char	*new_var;
	char	**new_env;
	int		name_len;
	int		error;
	int		var_index;
}			t_cd;

/*****************************export****************************************/

int			ft_export(t_token *token, t_minishell *minishell, int i);
int			ft_unset(t_token *token, t_minishell *minishell, int i);

/*******************************echo****************************************/

int			ft_echo(t_token *token, int i);

/********************************cd*****************************************/

int			ft_cd(t_token *token, int i, t_minishell *minishell);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
int			copy_new_env(t_minishell *minishell, char **new_env, char *new_var);
int			check_var_exist(t_minishell *minishell, const char *name,
				int name_len);
int			replace_existing_var(t_minishell *minishell, char *new_var,
				int var_index);
void		declare_putenv(t_cd *cd, const char *name);

/*********************************exit***************************************/

void		ft_exit(t_token *token, t_minishell *minishell, int i);

/****************************************************************************/

#endif