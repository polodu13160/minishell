/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:00:44 by antbonin          #+#    #+#             */
/*   Updated: 2025/04/23 15:00:47 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	check_token(t_token *token, char **env, t_minishell minishell)
// {
// 	int	i;

// 	char **envp;
// 	char	cwd[2048];
// 	i = 0;
// 	if (!token)
// 	{
// 		printf("Error: Tokenization failed\n");
// 		return ;
// 	}
// 	while (token[i].value)
// 	{
// 		printf("value : %s, type ; %d\n", token[i].value, token[i].type);
// 		i++;
// 	}
// 	if (!ft_strncmp(token[0].value, "echo", 4))
// 		ft_echo(count_tokens(minishell.line), ft_split(minishell.line, ' '));
// 	else if (!ft_strncmp(token[0].value, "cd", 2))
// 		cd(&token->value);
// 	else if (!ft_strncmp(token[0].value, "exit", 4))
// 		free_error(token, minishell);
// 	else if (!ft_strncmp(token[0].value, "pwd", 3))
// 	{
// 		if (getcwd(cwd, sizeof(cwd)) != NULL)
// 			printf("%s\n", cwd);
// 	}
// 	else if (!ft_strncmp(token[0].value, "env", 3))
// 	{
// 		envp = env;
// 		while (*envp)
// 			printf("%s\n", *envp++);
// 	}
// }