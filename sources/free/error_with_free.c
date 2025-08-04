/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_with_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:56:12 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/04 16:20:35 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
# include "stdlib.h"
#include "stdio.h"

int	free_and_close(char *value1, int *save_text, int return_error)
{
	if (value1 != NULL)
		free(value1);
	ft_close(save_text);
	return (return_error);
}

void	*ft_error_free_tab(t_token *tab)
{
	int	i;

	i = 0;
	free(tab);
	return (NULL);
}

void	ft_free_all(void *value, char *text, int perrorornot, int exitornot)
{
	free(value);
	if (perrorornot == 1)
		perror(text);
	if (exitornot == 1)
		exit(1);
}
