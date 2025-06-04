// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ast.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/21 22:19:10 by pde-petr          #+#    #+#             */
// /*   Updated: 2025/06/04 02:03:19 by pde-petr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ast.h"

// // int	reorganize_args_in_ast(t_minishell *minishell)
// // {
// // 	int		i;
// // 	int		j;
// // 	t_token	save[2];
// // 	char	*print;
// // 	int		check;

// // 	i = 0;
// // 	while (minishell->pipex_cmd[i])
// // 	{
// // 		j = 0;
// // 		check = 1;
// // 		while (minishell->pipex_cmd[i][j].value)
// // 		{
// // 			if (minishell->pipex_cmd[i][j].type == T_REDIRECT_IN)
// // 			{
// // 				if (minishell->pipex_cmd[i][j + 1].value == NULL
// // 					|| (minishell->pipex_cmd[i][j + 1].type != T_FUNC
// // 						&& minishell->pipex_cmd[i][j + 1].type != T_WORD))
// // 				{
// // 					print = ft_strjoin("syntax error near unexpected token after redirect in :",
// // 							minishell->pipex_cmd[i][j + 1].value);
// // 					ft_putstr_fd(print, 2);
// // 					free(print);
// // 					return (1);
// // 				}
// // 				save[0] = minishell->pipex_cmd[i][j];
// // 				save[1] = minishell->pipex_cmd[i][j + 1];
// // 				minishell->pipex_cmd[i][j] = minishell->pipex_cmd[i][check - 1];
// // 				minishell->pipex_cmd[i][j + 1] = minishell->pipex_cmd[i][check];
// // 				minishell->pipex_cmd[i][check - 1] = save[0];
// // 				minishell->pipex_cmd[i][check] = save[1];
// // 				check+= 2;
// // 				// j++;
// // 			}
// // 			j++;
// // 		}
// // 		i++;
// // 	}
// // 	//   printf("%s = numero 1 \n", save[0].value);
// // 	//   printf("%s = numero 2 \n", save[1].value);
// // 	j = 0;
// // 	while (minishell->pipex_cmd[j] != NULL)
// // 	{
// // 		i = 0;
// // 		while (minishell->pipex_cmd[j][i].value != NULL)
// // 		{
// // 			ft_putstr_fd(minishell->pipex_cmd[j][i++].value, 2);
// // 			printf("\n");
// // 		}
// // 		j++;
// // 	}
// // 	return (0);
// // }

// // int	ft_ast_token(t_token *tokens, t_minishell *minishell)
// // {
// // 	int		*cut_tokens;
// // 	int		i;
// // 	int		j;
// // 	int		x;
// // 	int		check;
// // 	char	*print;

// // 	check = 0;
// // 	i = minishell->count_tokens;
// // 	minishell->nb_pipe = 0;
// // 	while (--i != -1)
// // 	{
// // 		if ((i == minishell->count_tokens - 1) && (tokens[i].type != T_WORD
// // 				&& tokens[i].type != T_FUNC))
// // 		{
// // 			print = ft_strjoin("syntax error near unexpected token :",
// // 					tokens[i].value);
// // 			ft_putstr_fd(print, 2);
// // 			free(print);
// // 			return (1);
// // 		}
// // 		if (tokens[i].type == T_PIPE)
// // 			minishell->nb_pipe++;
// // 	}
// // 	minishell->pipex_cmd = ft_calloc(minishell->nb_pipe + 2, sizeof(t_token *));
// // 	minishell->pipex_cmd[minishell->nb_pipe + 1] = NULL;
// // 	j = 0;
// // 	while (1)
// // 	{
// // 		i++;
// // 		if (tokens[i].type == T_PIPE || tokens[i].value == NULL)
// // 		{
// // 			x = 0;
// // 			if (tokens[check].type == T_PIPE)
// // 				check++;
// // 			minishell->pipex_cmd[j] = ft_calloc(i - check + 1, sizeof(t_token));
// // 			minishell->pipex_cmd[j][i - check].value = NULL;
// // 			while (check < i)
// // 			{
// // 				minishell->pipex_cmd[j][x++] = tokens[check++];
// // 			}
// // 			if (tokens[i].value == NULL)
// // 				break ;
// // 			j++;
// // 		}
// // 	}
// // 	return (reorganize_args_in_ast(minishell));
// // }
// // int	ft_count_cmd(t_token *tokens, int limit_pipe)
// // {
// // 	int	count_cmd;
// // 	int	i;
// // 	int	count_pipe;

// // 	count_cmd = 0;
// // 	i = 0;
// // 	count_pipe = 0;
// // 	while (tokens[i].value)
// // 	{
// // 		if (tokens[i].type == T_PIPE)
// // 			count_pipe++;
// // 		else if (count_pipe > limit_pipe)
// // 			break ;
// // 		else if (count_pipe == limit_pipe)
// // 			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
// // 				count_cmd++;
// // 		i++;
// // 	}
// // 	return (count_cmd);
// // }

// // int	ft_join_tab_cmd(t_token *tokens, int limit_pipe, char **malloc_cmd,
// // 		int count_pipe)
// // {
// // 	int	i;
// // 	int	j;

// // 	i = -1;
// // 	j = 0;
// // 	while (tokens[i].value)
// // 	{
// // 		if (tokens[i].type == T_PIPE)
// // 			count_pipe++;
// // 		else if (count_pipe > limit_pipe)
// // 			break ;
// // 		else if (count_pipe == limit_pipe)
// // 			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
// // 			{
// // 				malloc_cmd[j++] = tokens[i].value;
// // 			}
// // 		i++;
// // 	}
// // 	return (j);
// // }

// // char	**ft_store_cmd(t_token *tokens, int limit_pipe)
// // {
// // 	int		count_pipe;
// // 	int		count_cmd;
// // 	int		last_index_cmd;
// // 	char	**malloc_cmd;

// // 	count_pipe = 0;
// // 	count_cmd = ft_count_cmd(tokens, limit_pipe);
// // 	malloc_cmd = ft_calloc(count_cmd + 1, sizeof(char *));
// // 	if (malloc_cmd == NULL)
// // 		return (NULL);
// // 	last_index_cmd = ft_join_tab_cmd(tokens, limit_pipe, malloc_cmd,
// // 			count_pipe);
// // 	malloc_cmd[last_index_cmd] = NULL;
// // 	return (malloc_cmd);
// // }




// int	ft_count_infiles(t_token *tokens, int limit_pipe)
// {
// 	int	count_infiles;
// 	int	i;
// 	int	count_pipe;

// 	count_infiles = 0;
// 	i = 0;
// 	count_pipe = 0;
// 	while (tokens[i].value)
// 	{
// 		tokens[i].fd = -1;
// 		if (tokens[i].type == T_PIPE)
// 		{
// 			count_pipe++;
// 			if (count_pipe == limit_pipe)
// 				count_infiles++;
// 		}
// 		else if (count_pipe > limit_pipe)
// 			break ;
// 		else if (count_pipe == limit_pipe)
// 			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
// 				count_infiles++;
// 		i++;
// 	}
// 	return (count_infiles);
// }

// int	ft_join_tab_infiles(t_token *tokens, int limit_pipe,
// 		t_token *malloc_infiles, int count_pipe)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	while (tokens[++i].value)
// 	{
// 		if (tokens[i].type == T_PIPE)
// 		{
// 			if ((++count_pipe) == limit_pipe)
// 				malloc_infiles[j++] = tokens[i];
// 		}
// 		else if (count_pipe == limit_pipe)
// 			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
// 			{
// 				if (tokens[i].type == T_REDIRECT_IN)
// 				{
// 					free(tokens[i].value);
// 					tokens[i].value = ft_strdup(tokens[i + 1].value);
// 				}
// 				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
// 				malloc_infiles[j++] = tokens[i];
// 			}
// 	}
// 	return (j);
// }

// t_token	*ft_store_infiles(t_token *tokens, int limit_pipe)
// {
// 	int		count_infiles;
// 	int		last_index_malloc_infiles;
// 	t_token	*malloc_infiles;

// 	count_infiles = ft_count_infiles(tokens, limit_pipe);
// 	malloc_infiles = ft_calloc(count_infiles + 1, sizeof(t_token));
// 	if (malloc_infiles == NULL)
// 		return (NULL);
// 	last_index_malloc_infiles = ft_join_tab_infiles(tokens, limit_pipe,
// 			malloc_infiles, 0);
// 	malloc_infiles[last_index_malloc_infiles].value = NULL;
// 	return (malloc_infiles);
// }