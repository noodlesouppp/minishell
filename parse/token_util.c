/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:32:27 by yousong           #+#    #+#             */
/*   Updated: 2025/02/19 16:31:05 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	handle_d_redir(t_token *info, int *pos)
{
	if (*pos > 0)
		info->t[(*info->i)++] = ft_substr(info->l, info->s, *pos - info->s);
	info->t[(*info->i)++] = ft_substr(info->l, *pos, 2);
	*pos += 1;
	info->s = *pos + 1;
}

void	handle_sp_cmd(t_token *info, int *pos)
{
	if (*pos > 0)
		info->t[(*info->i)++] = ft_substr(info->l, info->s, *pos - info->s);
	info->t[(*info->i)++] = ft_substr(info->l, *pos, 1);
	info->s = *pos + 1;
}

static int	count_nonempty(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			count = count + 1;
		i = i + 1;
	}
	return (count);
}

static char	**copy_nonempty(char **tokens, int count)
{
	char	**new_tokens;
	int		i;
	int		j;

	new_tokens = malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
		{
			new_tokens[j] = tokens[i];
			j = j + 1;
		}
		else
			free(tokens[i]);
		i = i + 1;
	}
	new_tokens[j] = NULL;
	free(tokens);
	return (new_tokens);
}

char	**remove_empty(char **tokens)
{
	char	**new_tokens;
	int		count;

	count = count_nonempty(tokens);
	new_tokens = copy_nonempty(tokens, count);
	// free(tokens);
	return (new_tokens);
}
