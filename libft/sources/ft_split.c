/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:11:33 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/21 18:07:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdlib.h>

int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**cpysplit(char *str, char c, char **tab, int i)
{
	int	j;
	int	k;

	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			k = 0;
			while (str[i + k] != c && str[i + k])
				k++;
			tab[j] = ft_calloc(k + 1, sizeof(char));
			if (!tab[j])
			{
				free_tab(tab);
				return (0);
			}
			ft_strlcpy(tab[j], &str[i], k + 1);
			j++;
			i += k;
		}
		else
			i++;
	}
	return (tab);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(count_words(str, c) + 1, sizeof(char *));
	if (!tab)
		return (0);
	tab = cpysplit(str, c, tab, i);
	return (tab);
}
