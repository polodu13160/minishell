/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:00:44 by antbonin          #+#    #+#             */
/*   Updated: 2025/05/10 14:44:28 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char	*expand_env_vars(char *str, t_minishell minishell)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*var_name;
// 	char	*value;
// 	char	*result;
// 	char	*temp;
// 	char	c[2];

// 	i = 0;
// 	c[1] = '\0';
// 	result = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && str[i
// 			+ 1] != '"')
// 		{
// 			start = i + 1;
// 			end = start;
// 			while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
// 				end++;
// 			var_name = ft_substr(str, start, end - start);
// 			if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
// 				value = ft_itoa(minishell.code_error);
// 			else
// 				value = get_env_value(var_name, minishell.env);
// 			temp = result;
// 			result = ft_strjoin(result, value);
// 			free(temp);
// 			free(value);
// 			free(var_name);
// 			i = end;
// 		}
// 		else
// 		{
// 			c[0] = str[i];
// 			temp = result;
// 			result = ft_strjoin(result, c);
// 			free(temp);
// 			i++;
// 		}
// 	}
// 	return (result);
// }