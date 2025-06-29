/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:44:41 by antbonin          #+#    #+#             */
/*   Updated: 2025/06/29 22:57:05 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "token.h"
#include <readline/readline.h>

int	check_interrupt(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

int	write_here_doc(int i, int j, t_token *tokens, int save_text)
{
	char	*read_like_gnl;

	read_like_gnl = NULL;
	setup_signals_child();
	rl_event_hook = check_interrupt;
	while (j++ == 0 || read_like_gnl[0] == 0 || ft_strcmp(read_like_gnl,
			tokens[i + 1].value))
	{
		if (j != 0)
		{
			if ((read_like_gnl != NULL) && g_sig != SIGINT && (write(save_text,
						read_like_gnl, ft_strlen(read_like_gnl)) == -1
					|| write(save_text, "\n", 1) == -1))
			{
				return (free_and_close(read_like_gnl, &save_text, 4));
			}
			free(read_like_gnl);
		}
		read_like_gnl = readline(">");
		if (g_sig == SIGINT)
		{
			free(read_like_gnl);
			close(save_text);
			rl_event_hook = NULL;
			return (130);
		}
		if (read_like_gnl == NULL)
			return (free_and_close(read_like_gnl, &save_text, 3));
	}
	free(read_like_gnl);
	setup_signals();
	if (ft_close(&save_text) == -1)
		free_and_close(read_like_gnl, &save_text, 4);
	return (0);
}
