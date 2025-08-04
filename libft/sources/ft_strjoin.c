/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:07:46 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/16 15:11:53 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	if (s2 != NULL)
		j = ft_strlen(s2);
	else
		j = 0;
	str = ft_calloc(i + j + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
