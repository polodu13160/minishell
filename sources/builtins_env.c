/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/16 15:18:03 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "pipex.h"
#include "stdio.h"

int	check_builtins(t_minishell *minishell, int i)
{
	if (minishell->pipex[i].cmd && minishell->pipex[i].cmd[0] != NULL)
	{
		if (ft_strncmp(minishell->pipex[i].cmd[0], "echo", 5) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "cd", 3) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "exit", 5) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "env", 4) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "pwd", 4) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "export", 7) == 0)
			return (1);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "unset", 6) == 0)
			return (1);
	}
	i++;
	return (0);
}

int	apply_builtins(t_minishell *minishell, int i, t_pip *exec)
{
	if (minishell->pipex[i].cmd && minishell->pipex[i].cmd[0] != NULL)
	{
		if (ft_strncmp(minishell->pipex[i].cmd[0], "echo", 5) == 0)
			return (ft_echo(minishell->pipex[i].cmd, i));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "cd", 3) == 0)
			return (ft_cd(minishell->pipex[i].cmd, i, minishell));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "exit", 5) == 0)
			ft_exit(minishell->pipex[i].cmd, minishell, i, exec);
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "env", 4) == 0)
			return (minishell->code_error = ft_env(minishell, 0));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "pwd", 4) == 0)
			return (ft_env(minishell, 1));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "export", 7) == 0)
			return (ft_export(minishell->pipex[i].cmd, minishell, i));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "unset", 6) == 0)
			return (ft_unset(minishell->pipex[i].cmd, minishell, i));
	}
	i++;
	finish(exec, minishell, 0);
	return (-1);
}
