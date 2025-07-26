/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:13:29 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/26 20:13:36 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strcmp_whithout_equality(char *env, char *str)
{
	while (*env != '=' && *env != '\0')
	{
		if (*str != *env)
			return (1);
		if ((*str == '=' && *str == '\0'))
			break ;
		env++;
		str++;
	}
	if (*str != *env)
		return (1);
	return (0);
}
