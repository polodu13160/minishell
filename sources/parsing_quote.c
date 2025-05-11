/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/11 17:43:55 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_strlen_quote(char *str)
{
	int	i;
	int	j;

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

char	*check_quote_command(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	if (str[0] == '$')
		str = ft_strtrim(str, "$");
	copy = malloc(sizeof(char *) * (ft_strlen_quote(str) + 1));
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		else
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}

char	*parsing_one_quote(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	if (str[i] == '"')
		i++;
	if (str[i] == '$')
		while (str[i + j] != '"')
			j++;
	copy = malloc(sizeof(char) * j);
	if (!copy)
		return (NULL);
	j = 0;
	while (str[i] != '"')
	{
		copy[j] = str[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}

char	*parse_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	if (str[0] == '\'')
		i = 1;
	while (str[i] && str[i] != '\'')
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}
