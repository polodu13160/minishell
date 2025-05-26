/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldepetrini <pauldepetrini@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:07:56 by pde-petr          #+#    #+#             */
/*   Updated: 2025/05/26 11:20:46 by pauldepetri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>

t_token	*ft_check_outfiles(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_outfiles;
	int		j;
	t_token	*malloc_outfiles;

	count_pipe = 0;
	i = 0;
	count_outfiles = 0;
	malloc_outfiles = NULL;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
				count_outfiles++;
		i++;
	}
	count_pipe = 0;
	malloc_outfiles = ft_calloc(count_outfiles + 1, sizeof(t_token));
	if (malloc_outfiles == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_APPEND || tokens[i].type == T_REDIRECT_OUT)
			{
				tokens[i].new_value = tokens[i + 1].value;
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_outfiles[j++] = tokens[i];
			}
		i++;
	}
	malloc_outfiles[j].new_value = NULL;
	return (malloc_outfiles);
}

t_token	*ft_check_infiles(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_infiles;
	int		j;
	t_token	*malloc_infiles;

	count_pipe = 0;
	i = 0;
	count_infiles = 0;
	malloc_infiles = NULL;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
				count_infiles++;
		i++;
	}
	count_pipe = 0;
	malloc_infiles = ft_calloc(count_infiles + 1, sizeof(t_token));
	if (malloc_infiles == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_HEREDOC || tokens[i].type == T_REDIRECT_IN)
			{
				if (tokens[i].type == T_REDIRECT_IN)
					tokens[i].new_value = tokens[i + 1].value;
				tokens[i + 1].type = T_WORD_FOR_REDIRECT;
				malloc_infiles[j++] = tokens[i];
			}
		i++;
	}
	malloc_infiles[j].new_value = NULL;
	return (malloc_infiles);
}

char  **ft_check_cmd(t_token *tokens, int var_count_pipe)
{
	int		i;
	int		count_pipe;
	int		count_cmd;
	int		j;
	char **malloc_cmd;

	count_pipe = 0;
	i = 0;
	count_cmd = 0;
	malloc_cmd = NULL;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD) 
				count_cmd++;
		i++;
	}
	count_pipe = 0;
	
	malloc_cmd = ft_calloc(count_cmd + 1, sizeof(char *));
	if (malloc_cmd == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == T_PIPE)
			count_pipe++;
		else if (count_pipe > var_count_pipe)
			break ;
		else if (count_pipe == var_count_pipe)
			if (tokens[i].type == T_FUNC || tokens[i].type == T_WORD)
			{
				malloc_cmd[j++] = tokens[i].value;
			}
		i++;
	}
	malloc_cmd[j]= NULL;	
	return (malloc_cmd);
		
}

int	count_pipe(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == T_PIPE)
			count++;
		i++;
	}
	return (count);
}

int	ft_prepare_to_pipex(t_minishell *minishell, t_token *tokens)
{
	int var_count_pipe;
	var_count_pipe = 0;
	
	minishell->pipex = ft_calloc(count_pipe(tokens)+1, sizeof(t_pipex));
	while (var_count_pipe <= count_pipe(tokens))
	{
		
		minishell->pipex[var_count_pipe].infiles = ft_check_infiles(tokens,
				var_count_pipe);
		
		minishell->pipex[var_count_pipe].outfiles = ft_check_outfiles(tokens,
				var_count_pipe);
		minishell->pipex[var_count_pipe].cmd = ft_check_cmd(tokens,
				var_count_pipe);
		minishell->pipex[var_count_pipe].init = 0;
		
		var_count_pipe++;
	}
	minishell->pipex[var_count_pipe].init = 1;
	int i = 0;
	int j = 0;
	//free tout ca 
	while (minishell->pipex[j].init != 1)
	{
		printf("pipe n  %d\n", j);
		i = 0;
		while(minishell->pipex[j].infiles[i].new_value != NULL)
		{
			printf("infile %s\n", minishell->pipex[j].infiles[i].new_value);
			i++;
		}
		i = 0;
		while(minishell->pipex[j].outfiles[i].new_value != NULL)
		{
			printf("outfile %s\n", minishell->pipex[j].outfiles[i].new_value);
			i++;
		}
		i = 0;
		while(minishell->pipex[j].cmd[i] != NULL)
		{
			printf("cmd %s\n" ,minishell->pipex[j].cmd[i]);
			i++;
		}
		j++;
	}
	
	return 0;
}