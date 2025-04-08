/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:04:37 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/08 13:49:55 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	ft_pwd(void)
{
	char *pwd ;
	
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("getcwd");
		return 1;
	}
	write(1, pwd, sizeof(pwd));
	free(pwd);
	return (0);
}

int	main(void)
{
	ft_pwd();
	return (0);
}