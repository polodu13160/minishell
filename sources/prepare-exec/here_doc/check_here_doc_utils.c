/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:44:41 by antbonin          #+#    #+#             */
/*   Updated: 2025/08/06 14:59:23 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "use_free.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_close_here_doc(int i, t_minishell *minishell, t_pip *exec, int error)
{
	int	j;

	j = -1;
	if (error == 0)
	{
		while (minishell->pipex[i].infiles[++j].value)
			if (exec->fd_infile.value != minishell->pipex[i].infiles[j].value
				&& minishell->pipex[i].infiles[j].type == T_HEREDOC)
				ft_close(&(minishell->pipex[i].infiles[j].fd));
	}
	else
	{
		i = 0;
		while (minishell->pipex[i].infiles != NULL)
		{
			j = -1;
			while (minishell->pipex[i].infiles[++j].value)
				if (minishell->pipex[i].infiles[j].type == T_HEREDOC)
					ft_close(&(minishell->pipex[i].infiles[j].fd));
			i++;
		}
	}
}
int	while_write_here_doc(char *read_like_gnl, t_token *tokens, int save_text,
		int i)
{
	int	j;

	j = 0;
	while (j++ == 0 || read_like_gnl[0] == 0 || ft_strcmp(read_like_gnl,
			tokens[i + 1].value))
	{
		if ((read_like_gnl != NULL) && g_sig != SIGINT && (write(save_text,
					read_like_gnl, ft_strlen(read_like_gnl)) == -1
				|| write(save_text, "\n", 1) == -1))
			return (free_and_close(read_like_gnl, &save_text, 4));
		free(read_like_gnl);
		read_like_gnl = readline(">");
		if (g_sig == SIGINT)
		{
			free(read_like_gnl);
			close(save_text);
			g_sig = 10;
			return (130);
		}
		if (read_like_gnl == NULL)
			return (free_and_close(read_like_gnl, &save_text, 3));
	}
	return (0);
}

int	write_here_doc(int i, t_token *tokens, int save_text)
{
	char	*read_like_gnl;
	int		return_while;

	read_like_gnl = NULL;
	setup_signals_heredoc();
	rl_event_hook = check_interrupt;
	return_while = while_write_here_doc(read_like_gnl, tokens, save_text, i);
	rl_event_hook = NULL;
	if (return_while != 0)
	{
		setup_signals_child();
		rl_event_hook = NULL;
		return (return_while);
	}
	free(read_like_gnl);
	setup_signals_child();
	rl_event_hook = NULL;
	g_sig = 0;
	ft_close(&save_text);
	return (0);
}
