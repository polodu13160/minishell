/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_double_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/24 21:07:31 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int ft_strlen_quote(char *str)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			j++;
		i++;
	}
	return (i - j);
}

char *check_quote_command(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	char *copy;
	copy = malloc(sizeof(char) * (ft_strlen_quote(str) + 1));
	if (!copy)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			copy[j] = str[i];
			j++;
			i++;
		}
		if (!str[i])
			break;
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}
