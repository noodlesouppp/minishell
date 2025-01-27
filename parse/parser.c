/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:02:03 by yousong           #+#    #+#             */
/*   Updated: 2025/01/23 22:33:45 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

t_cmd	*parse_cmd(char *line)
{
	t_cmd	*cmd;
	char	**token;
	char	**tmp;

	while (*line == ' ')
		line++;
	if (!*line)
		return (NULL);
	token = get_space_token(line);
	tmp = token;
	token = get_cmd_token(tmp);
	free_tokens(tmp);
	if (check_error(token) < 0)
	{
		free_tokens(token);
		return (NULL);
	}
	token = check_path(token);
	cmd = get_cmd_info(token);
	free_tokens(token);
	return (cmd);
}