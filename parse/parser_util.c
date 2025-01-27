/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:35:34 by yousong           #+#    #+#             */
/*   Updated: 2025/01/27 16:43:48 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}

/* returns if a character is a special command or nah */

int	is_cmd(char *line, int i)
{
	if (!line)
		return (-1);
	if (!ft_strncmp(line + i, ">>", 2) || !ft_strncmp(line + i, "<<", 2))
		return (D_REDIR);
	else if (line[i] == '>' || line[i] == '<')
		return (REDIR);
	else if (line[i] == '|')
		return (PIPE);
	else
		return (0);
}

/* returns if a character is inside quotes or nah*/

int	is_in_quote(char *line, int idx)
{
	int	i;
	int	quote_flag;

	quote_flag = 0;
	i = -1;
	while (++i < idx + 1)
	{
		if (line[i] == '"')
		{
			if (quote_flag == 0)
				quote_flag = DQOUTE;
			else if (quote_flag == DQOUTE)
				quote_flag = 0;
		}
		else if (line[i] == '\'')
		{
			if (quote_flag == 0)
				quote_flag = SQOUTE;
			else if (quote_flag == SQOUTE)
				quote_flag = 0;
		}
	}
	return (quote_flag);
}