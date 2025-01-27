/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:58:01 by yousong           #+#    #+#             */
/*   Updated: 2025/01/27 16:37:57 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* tokenises input line based on spaces 
	respects quotes
	returns the final index */

int	tokenise_space(char **token, char *line, int *index, int *start)
{
	int	i;
	int	space;

	i = 0;
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			space = 0;
			token[*index] = ft_substr(line, *start, i - *start);
			while (line[i + space] == ' ')
				space++;
			if (!line[i + space])
				break ;
			*start = i + space;
			(*index)++;
		}
		i++;
	}
	return (i);
}

/* counts the no. of space-seperated tokens in the input*/

int	count_space(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
				return (count);
			count++;
		}
		i++;
	}
	return (count);
}

/* Splits the line into tokens separated by space
	ignores spaces inside quotes 
	splits and pre-filters tokens first for get_cmd_token */

char	**get_space_token(char *line)
{
	char	**token;
	int		i;
	int		start;
	int		index;

	start = 0;
	index = 0;
	token = (char **)malloc(sizeof(char *) * (count_space(line) + 2));
	i = tokenise_space(token, line, &index, &start);
	if (!line[i])
		token[index] = ft_substr(line, start, i - start);
	token[index + 1] = NULL;
	return (token);
}
