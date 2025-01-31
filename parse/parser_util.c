/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:35:34 by yousong           #+#    #+#             */
/*   Updated: 2025/01/31 17:01:24 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* first calculates the resulting len excluding any quotes, 
	then duplicates the resulting string */

char	*rm_quote_strdup(char *s1)
{
	char	*dup;
	int		len;
	int		i;
	int		dup_idx;

	len = ft_strlen(s1);
	i = -1;
	while (s1[++i])
		if (((s1[i] == '"' && is_in_quote(s1, i) != SQUOTE)
				|| (s1[i] == '\'' && is_in_quote(s1, i) != DQUOTE)))
			len--;
	dup = malloc(sizeof(char) * (len + 1));
	i = -1;
	dup_idx = 0;
	while (s1[++i])
	{
		while (((s1[i] == '"' && is_in_quote(s1, i) != SQUOTE)
				|| (s1[i] == '\'' && is_in_quote(s1, i) != DQUOTE)))
			i++;
		if (s1[i] == '\0')
			break ;
		dup[dup_idx++] = s1[i];
	}
	dup[dup_idx] = '\0';
	return (dup);
}

/* duplicates 2d array up until specified no. of strings and returns new copy */

char	**ft_array_dup(char **arr, int len)
{
	char	**new;
	int		i;

	i = 0;
/*	if (!arr)
	{
		printf("DEBUG: ft_array_dup called with NULL\n");
		return (NULL);
	}*/
	new = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

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
				quote_flag = DQUOTE;
			else if (quote_flag == DQUOTE)
				quote_flag = 0;
		}
		else if (line[i] == '\'')
		{
			if (quote_flag == 0)
				quote_flag = SQUOTE;
			else if (quote_flag == SQUOTE)
				quote_flag = 0;
		}
	}
	return (quote_flag);
}
