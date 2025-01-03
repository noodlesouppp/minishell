/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:12:46 by yousong           #+#    #+#             */
/*   Updated: 2025/01/03 03:50:05 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_node	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_list(&stash, fd);
	if (stash == NULL)
		return (NULL);
	line = ft_line(stash);
	ft_leftover(&stash);
	return (line);
}

void	ft_list(t_node **stash, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_newline(*stash))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		char_read = (int)read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_append(stash, buf);
	}
}

void	ft_append(t_node **stash, char *buf)
{
	t_node	*new;
	t_node	*end;

	end = ft_last_t_node(*stash);
	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	if (!end)
		*stash = new;
	else
		end->next = new;
	new->content = buf;
	new->next = NULL;
}

char	*ft_line(t_node *stash)
{
	int		length;
	char	*next_line;

	if (!stash)
		return (NULL);
	length = count_to_newline(stash);
	next_line = malloc(length + 1);
	if (!next_line)
		return (NULL);
	ft_strcpy(stash, next_line);
	return (next_line);
}

void	ft_leftover(t_node **stash)
{
	t_node	*end;
	t_node	*clean;
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean = malloc(sizeof(t_node));
	if (buf == NULL || clean == NULL)
		return ;
	end = ft_last_t_node(*stash);
	while (end->content[i] && end->content[i] != '\n')
		++i;
	while (end->content[i] && end->content[++i])
		buf[j++] = end->content[i];
	buf[j] = '\0';
	clean->content = buf;
	clean->next = NULL;
	ft_dealloc(stash, clean, buf);
}

/*int	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
    	perror("Error opening file");
    	return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s\n", line);
		free(line);
	}
	return (0);
}*/
