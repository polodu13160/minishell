/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:08:24 by paul              #+#    #+#             */
/*   Updated: 2025/05/11 21:08:25 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int ft_check_here_doc(t_token *tokens, t_minishell *minishell)
{
    int i;
    char *gnl;
    int *save_text;

    i = 0;
    minishell->nb_here_doc = 0;
    while (tokens[i].value)
    {
        tokens[i].new_value = NULL;
        if (tokens[i].type == T_HEREDOC)
        {
            if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_FUNC)
            {
                print = ft_strjoin("syntax error near unexpected token after redirect in :",
                                   minishell->pipex_cmd[i][j + 1].value);
                ft_putstr_fd(print, 2);
                free(print);
                return (1);
            }
            if (pipe(save_text) == -1)
            {
                perror("pipe error");
                return (1);
            }
            ft_putstr_fd(">", 1);

            gnl = get_next_line(0);
            if (gnl == NULL)
            {
                perror("get_next_line error");
                return (1);
            }
            while (gnl && ft_strncmp(gnl, tokens[i + 1].value, ft_strlen(tokens[i + 1].value)))
            {
                if (write(save_text[1], tokens[i + 1].value, ft_strlen(tokens[i + 1].value)) == -1)
                {
                    perror("write error");
                    return (1);
                }
                ft_putstr_fd(">", 1);
                free(gnl);
                gnl = get_next_line(0);
            }
            free(gnl);
            close(save_text[1]);
            (int)tokens[i].new_value =  save_text[0];
        }
        i++;
    }
    return (0);
}