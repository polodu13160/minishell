/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:28:18 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/16 14:14:19 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

/// @brief print env and export table
/// @param env is the env
/// @param set is all variables export
/// @return
int	ft_env(char **env, char **set)
{
	int	i;

	i = 0;
	if (env != NULL)
		while (env[i])
		{
			ft_putstr_fd(env[i], 1);
			ft_putchar_fd('\n', 1);
			i++;
		}
	i = 0;
	if (set != NULL)
		while (set[i])
		{
			ft_putstr_fd(set[i], 1);
			ft_putchar_fd('\n', 1);
			i++;
		}
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
//    return (ft_env(env));
// }