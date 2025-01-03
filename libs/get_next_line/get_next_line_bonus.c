/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:12:46 by yousong           #+#    #+#             */
/*   Updated: 2023/12/05 15:58:09 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_node	*stash[4096];
	char			*line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_list(stash, fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = ft_line(stash[fd]);
	ft_leftover(&stash[fd]);
	return (line);
}

void	ft_list(t_node **stash, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_newline(stash[fd]))
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
		ft_append(stash, buf, fd);
	}
}

void	ft_append(t_node **stash, char *buf, int fd)
{
	t_node	*new;
	t_node	*end;

	end = ft_last_t_node(stash[fd]);
	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	if (!end)
		stash[fd] = new;
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
