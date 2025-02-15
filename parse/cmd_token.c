/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:00:16 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:45:36 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* splits tokens into subtokens based on which special char it is 
	ignores any special characters if inside quotes 
	returns the start index of REMAINDER part of line */

int	tokenise_cmd(char **t, char *l, int pos, int *idx)
{
	t_token	info;
	int		type;

	info.t = t;
	info.l = l;
	info.i = idx;
	info.s = 0;
	while (l[++pos] != '\0')
	{
		if (!is_in_quote(l, pos))
		{
			type = is_cmd(l, pos);
			if (type == D_REDIR)
				handle_d_redir(&info, &pos);
			else if (type == PIPE || type == REDIR)
				handle_sp_cmd(&info, &pos);
		}
	}
	return (info.s);
}

/* adjusts total token count when encountering special characters
	skips over an iteration for double redirections */

void	check_for_cmd(char *line, int *i, int *count)
{
	if (is_cmd(line, *i) == D_REDIR)
	{
		if (*i > 0)
			(*count)++;
		(*i)++;
		if (line[*i + 1] != '\0')
			(*count)++;
	}
	else if (is_cmd(line, *i) == PIPE || is_cmd(line, *i) == REDIR)
	{
		if (*i > 0)
			(*count)++;
		if (line[*i + 1] != '\0')
			(*count)++;
	}
}

/* counts how many tokens there'll be after splitting on
	special characters ("", '', >> etc)*/

int	cmd_space(char **line)
{
	int	i;
	int	count;

	count = 0;
	while (*line)
	{
		i = -1;
		count++;
		while ((*line)[++i] != '\0')
			check_for_cmd(*line, &i, &count);
		line++;
	}
	return (count);
}

/* uses tokenise_cmd to split the tokens based on special chars 
	after tokenise_cmd it handles remainder part of token 
	e.g "ls>>out" becomes ["ls", ">>", "out"]     */

char	**get_cmd_token(char **line)
{
	char	**token;
	int		i;
	int		index;
	int		start;

	index = 0;
	token = (char **)malloc(sizeof(char *) * (cmd_space(line) + 1));
	while (*line)
	{
		i = -1;
		start = tokenise_cmd(token, *line, i, &index);
		if ((*line)[start] != '\0')
			token[index++] = ft_substr(*line, start, ft_strlen(*line) - start);
		line++;
	}
	token[index] = NULL;
	return (token);
}
