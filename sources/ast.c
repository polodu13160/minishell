/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:10 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/25 15:00:58 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"




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
	// minishell.nb_redirect_out = 0;
	// minishell.nb_here_doc = 0;
	// minishell.nb_redirect_in = 0;
	// minishell.nb_append = 0;
	// printf("%s\n", tokens[i - 1].value);
	while (--i != -1)
	{
		if ((i == minishell->count_tokens - 1) && (tokens[i].type != T_WORD
				&& tokens[i].type != T_FUNC))
		{
			print = ft_strjoin("syntax error near unexpected token :",
					tokens[i].value);
			ft_putstr_fd(print, 2);
			free(print);
			free_error(tokens, minishell);
			return (1);
		}
		if (tokens[i].type == T_PIPE)
			minishell->nb_pipe++;
		// if (i == minishell->count_tokens && tokens[i].type == T_PIPE)
		// {
		// 	ft_putstr_fd("No use pipe in last param", 2);
		// 	free_error(tokens,minishell);
		// }
		// else
		// {
		// if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
		// {
		// 	if (tokens[i+1].value == NULL || tokens[i+1].type != T_WORD)
		// 	{
		// 		ft_putstr_fd("syntax error", 2);
		// 		return (1);
		// 	}
		// 	else
		// 	{
		// 		tokens[i+1].type = T_DEL;
		// 		free(tokens[i].value);
		// 		tokens[i].value = ;
		// 	}
		// 	if (tokens[i].type ==  )
		// 	i--;
		// 	if (tokens[i].type == T_PIPE)
		// 	{
		// 		i--;
		// 		ft_create_file();
		// 		check+= 2;
		// 	}
		// 	else (tokens[i].type == T_REDIRECT_IN )
		// }
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
				break;
			j++;
		}
	}
	j = 0;
	// while (minishell->pipex_cmd[j] != NULL)
	// {
	// 	check = 0;
	// 	while (minishell->pipex_cmd[j][check].value != NULL)
	// 	{
	// 		ft_putstr_fd(minishell->pipex_cmd[j][check++].value, 2);
	// 		printf("\n");
	// 	}
	// 	printf("\nnew tab\n");
	// 	j++;
	// }
	reorganize_args_in_ast(minishell);
}
// while (tokens[i].value != NULL)
// {
// 	if (tokens[i].type == T_REDIRECT_IN)
// 		minishell.nb_redirect_in++;
// 	if (tokens[i].type == T_APPEND)
// 		minishell.nb_append++;
// 	if (tokens[i].type == T_REDIRECT_OUT)
// 		minishell.nb_redirect_out++;
// 	if (tokens[i].type == T_HEREDOC)
// 		minishell.nb_here_doc++;

// 	i++;
// }
// printf("\ncount_pipe = %d\n", minishell.nb_pipe);
// printf("\ncount_here_doc = %d\n", minishell.nb_here_doc);
// printf("\ncount_redirct in  = %d\n", minishell.nb_redirect_in);
// printf("\ncount_redirct out  = %d\n", minishell.nb_redirect_out);
// printf("\ncount_append  = %d\n", minishell.nb_append);
