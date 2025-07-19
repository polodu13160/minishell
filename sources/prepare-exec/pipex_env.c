/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:13:10 by pde-petr          #+#    #+#             */
/*   Updated: 2025/07/19 18:43:54 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_add_slash_to_env(t_pip *exec)
{
	char	*new_path;
	int		i;

	if (exec->path_args == NULL)
		return (0);
	i = 0;
	while (exec->path_args[i])
		i++;
	while (--i >= 0)
	{
		new_path = ft_strjoin(exec->path_args[i], "/");
		if (new_path == NULL)
			return (1);
		free(exec->path_args[i]);
		exec->path_args[i] = new_path;
	}
	return (0);
}

int	ft_set_path_env(t_pip *exec, char **env)
{
	char	*text;

	exec->path_args = NULL;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			text = ft_memchr(*env, '=', 5);
			text++;
			if (text == 0)
			{
				ft_printf_fd(2, "No path env\n");
				return (1);
			}
			exec->path_args = ft_split(text, ':');
			if (exec->path_args == NULL || ft_add_slash_to_env(exec) == 1)
			{
				ft_printf_fd(2, "Error Malloc\n");
				return (1);
			}
			break ;
		}
		env++;
	}
	return (0);
}

int	ft_exec_to_env(t_minishell *minishell, t_pip *exec, int i, int arg_exec)
{
	int		test_acces;
	char	*join;
	if (exec->path_args == NULL)
	{
		join = ft_strjoin("./", minishell->pipex[arg_exec].cmd[0]);
		if (join == NULL)
			return (10);
		if (access(join, F_OK) == 0)
		{
			minishell->pipex[arg_exec].cmd[0] = join;
			if (access(join, X_OK) == -1)
			{
				
				free(join);
				return (126);
			}
			else
				execve(join, minishell->pipex[arg_exec].cmd, exec->env);
		}
		free(join);
		return (127);
	}
	while (exec->path_args[i])
	{
		exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
				minishell->pipex[arg_exec].cmd[0]);
		if (exec->path_absolut_exec == NULL)
			return (10);
		test_acces = access(exec->path_absolut_exec, F_OK);
		if (test_acces == 0)
		{
			execve(exec->path_absolut_exec, minishell->pipex[arg_exec].cmd,
				exec->env);
			return (126);
		}
		free(exec->path_absolut_exec);
		exec->path_absolut_exec = NULL;
		i++;
	}
	return (127);
}
