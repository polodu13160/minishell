/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:14 by antbonin          #+#    #+#             */
/*   Updated: 2025/07/24 13:51:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "free.h"
#include "pipex.h"

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

int	apply_builtins(t_minishell *minishell, int i, t_pip *exec, int print_exit)
{
	if (minishell->pipex[i].cmd && minishell->pipex[i].cmd[0] != NULL
		&& minishell->pipex[i].cmd[0][0] != '\0')
	{
		if (ft_strncmp(minishell->pipex[i].cmd[0], "echo", 5) == 0)
			return (ft_echo(minishell->pipex[i].cmd));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "cd", 3) == 0)
			return (ft_cd(minishell->pipex[i].cmd, minishell, 0, 0));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "exit", 5) == 0)
			return (ft_exit(minishell->pipex[i].cmd, minishell, exec, print_exit));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "env", 4) == 0)
			return (minishell->return_command = ft_env(minishell, 0));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "pwd", 4) == 0)
			return (ft_env(minishell, 1));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "export", 7) == 0)
			return (ft_export(minishell->pipex[i].cmd, minishell, 0));
		else if (ft_strncmp(minishell->pipex[i].cmd[0], "unset", 6) == 0)
			return (ft_unset(minishell->pipex[i].cmd, minishell, 0));
	}
	else
		return (127);
	ft_finish(exec, minishell, 1, NULL);
	return (-1);
}
