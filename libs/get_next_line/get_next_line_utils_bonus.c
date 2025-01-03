/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:20:42 by yousong           #+#    #+#             */
/*   Updated: 2023/12/05 15:58:50 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_newline(t_node *stash)
{
	int	i;

	if (stash == NULL)
		return (0);
	while (stash != NULL)
	{
		i = 0;
		while (stash->content[i] && i < BUFFER_SIZE)
		{
			if (stash->content[i] == '\n')
				return (1);
			++i;
		}
		stash = stash->next;
	}
	return (0);
}

int	count_to_newline(t_node *stash)
{
	int	i;
	int	len;

	if (stash == NULL)
		return (0);
	len = 0;
	while (stash != NULL)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				++len;
				return (len);
			}
			i++;
			len++;
		}
		stash = stash->next;
	}
	return (len);
}

t_node	*ft_last_t_node(t_node *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next != NULL)
		stash = stash->next;
	return (stash);
}

void	ft_strcpy(t_node *stash, char *next_line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	j = 0;
	while (stash != NULL)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				next_line[j] = '\n';
				j++;
				next_line[j] = '\0';
				return ;
			}
			next_line[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	next_line[j] = '\0';
}

void	ft_dealloc(t_node **stash, t_node *clean, char *buf)
{
	t_node	*tmp;

	if (*stash == NULL)
		return ;
	while (*stash != NULL)
	{
		tmp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = tmp;
	}
	*stash = NULL;
	if (clean->content[0])
		*stash = clean;
	else
	{
		free(buf);
		free(clean);
	}
}
