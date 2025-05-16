/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:23 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/16 15:58:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "libft.h"
# include "token.h"
# include <stdlib.h>
# include <unistd.h>

void	ft_echo(t_token *token, int i);
int	cd(char **args);
#endif