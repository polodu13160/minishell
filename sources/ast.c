/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:10 by pde-petr          #+#    #+#             */
/*   Updated: 2025/05/11 21:14:27 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	reorganize_args_in_ast(t_minishell *minishell)
{
	int		i;
	int		j;
	t_token	save[2];
	char	*print;
	int		check;

	i = 0;
	while (minishell->pipex_cmd[i])
	{
		j = 0;
		check = 1;
		while (minishell->pipex_cmd[i][j].value)
		{
			if (minishell->pipex_cmd[i][j].type == T_REDIRECT_IN)
			{
				if (minishell->pipex_cmd[i][j + 1].value == NULL
					|| (minishell->pipex_cmd[i][j + 1].type != T_FUNC
						&& minishell->pipex_cmd[i][j + 1].type != T_WORD))
				{
					print = ft_strjoin("syntax error near unexpected token after redirect in :",
							minishell->pipex_cmd[i][j + 1].value);
					ft_putstr_fd(print, 2);
					free(print);
					return (1);
				}
				save[0] = minishell->pipex_cmd[i][j];
				save[1] = minishell->pipex_cmd[i][j + 1];
				minishell->pipex_cmd[i][j] = minishell->pipex_cmd[i][check - 1];
				minishell->pipex_cmd[i][j + 1] = minishell->pipex_cmd[i][check];
				minishell->pipex_cmd[i][check - 1] = save[0];
				minishell->pipex_cmd[i][check] = save[1];
				check+= 2;
				// j++;
			}
			j++;
		}
		i++;
	}
	//   printf("%s = numero 1 \n", save[0].value);
	//   printf("%s = numero 2 \n", save[1].value);
	j = 0;
	while (minishell->pipex_cmd[j] != NULL)
	{
		i = 0;
		while (minishell->pipex_cmd[j][i].value != NULL)
		{
			ft_putstr_fd(minishell->pipex_cmd[j][i++].value, 2);
			printf("\n");
		}
		j++;
	}
	return (0);
}

int	ft_ast_token(t_token *tokens, t_minishell *minishell)
{
	int		*cut_tokens;
	int		i;
	int		j;
	int		x;
	int		check;
	char	*print;

	check = 0;
	i = minishell->count_tokens;
	minishell->nb_pipe = 0;
	while (--i != -1)
	{
		if ((i == minishell->count_tokens - 1) && (tokens[i].type != T_WORD
				&& tokens[i].type != T_FUNC))
		{
			print = ft_strjoin("syntax error near unexpected token :",
					tokens[i].value);
			ft_putstr_fd(print, 2);
			free(print);
			return (1);
		}
		if (tokens[i].type == T_PIPE)
			minishell->nb_pipe++;
	}
	minishell->pipex_cmd = ft_calloc(minishell->nb_pipe + 2, sizeof(t_token *));
	minishell->pipex_cmd[minishell->nb_pipe + 1] = NULL;
	j = 0;
	while (1)
	{
		i++;
		if (tokens[i].type == T_PIPE || tokens[i].value == NULL)
		{
			x = 0;
			if (tokens[check].type == T_PIPE)
				check++;
			minishell->pipex_cmd[j] = ft_calloc(i - check + 1, sizeof(t_token));
			minishell->pipex_cmd[j][i - check].value = NULL;
			while (check < i)
			{
				minishell->pipex_cmd[j][x++] = tokens[check++];
			}
			if (tokens[i].value == NULL)
				break ;
			j++;
		}
	}
	return (reorganize_args_in_ast(minishell));
}
