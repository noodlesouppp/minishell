/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:00:16 by yousong           #+#    #+#             */
/*   Updated: 2025/01/26 08:08:56 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	tokenize_cmd(char **token, char *line, int i, int *idx)
{
	int	start;

	start = 0;
	while (line[++i] != '\0')
	{
		if (!is_in_quote(line, i))
		{
			if (is_cmd(line, i) == D_REDIR)
			{
				if (i > 0 && !is_cmd(line, i - 1))
					token[(*idx)++] = ft_substr(line, start, i - start);
				token[(*idx)++] = ft_substr(line, i, 2);
				i++;
				start = i + 1;
			}
			else if (is_cmd(line, i) == PIPE || is_cmd(line, i) == REDIR)
			{
				if (i > 0 && !is_cmd(line, i - 1))
					token[(*idx)++] = ft_substr(line, start, i - start);
				token[(*idx)++] = ft_substr(line, i, 1);
				start = i + 1;
			}
		}
	}
	return (start);
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

/* counts the no. of special command tokens in the input*/

int	cmd_space(char **line)
{
	int	i;
	int	count;

	while (*line)
	{
		i = 0;
		count++;
		while ((*line)[i++] != '\0')
			check_for_cmd(*line, &i, &count);
		line++;
	}
	return (count);
}

char	get_cmd_token(char **line)
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
		start = tokenize_cmd(token, *line, i, &index);
		if ((*line)[start] != '\0')
			token[index++] = ft_substr(*line, start, ft_strlen(*line) - start);
		line++;
	}
	token[index] = NULL;
	return (token);
}