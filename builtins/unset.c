/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:51:21 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/14 17:32:48 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

/// @brief it is the message of error's unset
/// @param
void	message_error_unset(void)
{
	ft_putstr_fd("unset: not enough arguments", 2);
}

static void	ft_delete_var(char **tab, char **variables)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	while (tab != NULL && tab[i])
	{
		j = 0;
		while (variables[j])
		{
			if (ft_strncmp(tab[i], variables[j], ft_strlen(variables[j])) == 0)
			{
				y = i;
				while (tab[y])
				{
					tab[y] = tab[y + 1];
					y++;
				}
			}
			j++;
		}
		i++;
	}
}

/// @brief for unset the variable in env global or in set (local),
///
/// @param variables are different unset variables
/// @param env is a env of minishell
/// @param set is a set (all variables) of minishell
/// @return
int	ft_unset(char **variables, char **env, char **set)
{
    if (variables == NULL || variables[0] == NULL)
		return (1);
	if (env != NULL)
		ft_delete_var(env, variables);
	if (set != NULL)
		ft_delete_var(set, variables);
	
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	// char *variable[] = NULL;
// 	char *set[] = {"triste", "tot", "k", NULL};
//     char *env[] = {"triste", "tot", "k", NULL};

//     if (ft_unset(NULL, env, set) == 1)
//     {
//         message_error_unset();
//         return 1;
//     }
// 	int i = 0;
// 	while(env[i])
// 	{
// 	    printf("%s\n", env[i]);
// 	    i++;
// 	}
//     return 0;
// }