/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:02:03 by yousong           #+#    #+#             */
/*   Updated: 2025/03/01 23:03:12 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*detokenise(char **tokens)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!tokens || !tokens[0])
		return (ft_strdup(""));
	result = ft_strdup("");
	i = 0;
	while (tokens[i])
	{
		tmp = result;
		result = ft_strjoin(tmp, tokens[i]);
		free(tmp);
		if (!result)
			return (NULL);
		if (tokens[i + 1])
		{
			tmp = result;
			result = ft_strjoin(tmp, " ");
			free(tmp);
		}
		i++;
	}
	return (result);
}

char	**get_tokens(char *line, t_env *env)
{
	char	**token;
	char	**tmp;
	char	*detoken;

	while (*line == ' ')
		line++;
	if (!*line)
		return (NULL);
	token = get_space_token(line);
	token = check_path(token, env);
	detoken = detokenise(token);
	free_tokens(token);
	token = get_space_token(detoken);
	free(detoken);
	tmp = token;
	token = get_cmd_token(tmp);
	free_tokens(tmp);
	if (check_error(token) < 0)
	{
		free_tokens(token);
		env->exit_stat = 2;
		return (NULL);
	}
	token = remove_empty(token);
	return (token);
}

t_cmd	*parse_cmd(char *line, t_env *env)
{
	t_cmd	*cmd;
	char	**token;

	token = get_tokens(line, env);
	if (!token)
		return (NULL);
	cmd = get_cmd_info(token, env);
	free_tokens(token);
	return (cmd);
}
