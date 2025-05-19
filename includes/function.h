/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/19 19:03:58 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "libft.h"
# include "token.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_echo(t_token *token, int i);
int		ft_cd(t_token *token, int i, t_minishell *minishell);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
int		copy_new_env(t_minishell *minishell, char **new_env, char *new_var);
int		check_var_exist(t_minishell *minishell, const char *name, int name_len);
#endif