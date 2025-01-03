/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:54:23 by yousong           #+#    #+#             */
/*   Updated: 2023/11/09 02:08:23 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include <stdlib.h>
#include "libft.h"

static int	ft_wc(const char *s, char c)
{
	int	count;
	int	lever;

	count = 0;
	lever = 0;
	while (*s)
	{
		if (*s == c)
			lever = 0;
		else if (lever == 0)
		{
			lever = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*range(const char *start, const char *end)
{
	size_t	len;
	char	*word;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	free_res(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free (result);
}

static char	**split_words(char const *s, char c, char **result)
{
	int			i;
	const char	*word_start;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			while (*s && *s != c)
				s++;
			result[i] = range(word_start, s);
			if (!result[i])
			{
				free_res(result, i);
				return (NULL);
			}
			i++;
		}
		while (*s && *s == c)
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int			wc;
	char		**result;

	if (!s)
		return (NULL);
	wc = ft_wc(s, c);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!result)
		return (NULL);
	if (*s == '\0')
	{
		result[0] = NULL;
		return (result);
	}
	while (*s && *s == c)
		s++;
	return (split_words(s, c, result));
}

/*int	main(void)
{
	const char	str[] = "xThexxPiratexxxKingxxxxisxmex";
	char	delimiter = 'x';
	char **result = ft_split(str, delimiter);

	if (result)
	{
		int i = 0;
		while (result[i] != NULL)
		{
			printf("word %d-%s\n", i, result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	else
	{
		printf("ft_split returned NULL\n");
	}
	return (0);
}*/
