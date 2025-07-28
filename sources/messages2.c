/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:38:30 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/28 16:35:12 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_export(t_minishell *minishell)
{
	int	j;

	j = 0;
	while (minishell->env[j])
	{
		ft_printf("%s\n", minishell->env[j]);
		j++;
	}
	return (0);
}

int	handle_invalid_identifier(char *var_name)
{
	printf("bash: export: `%s': not a valid identifier\n", var_name);
	return (1);
}
