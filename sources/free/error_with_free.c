/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_with_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:56:12 by pde-petr          #+#    #+#             */
/*   Updated: 2025/08/05 03:20:32 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"
#include "stdlib.h"

int	free_and_close(char *value1, int *save_text, int return_error)
{
	if (value1 != NULL)
		free(value1);
	ft_close(save_text);
	return (return_error);
}



void	free_value(void *value, char *text, int perrorornot, int exitornot)
{
	free(value);
	if (perrorornot == 1)
		perror(text);
	if (exitornot == 1)
		exit(1);
}
