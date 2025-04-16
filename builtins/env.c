/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:28:18 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/16 14:01:21 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "stdlib.h"

int	ft_env(char **env)
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
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
//    return (ft_env(env));
// }