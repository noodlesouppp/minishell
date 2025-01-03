/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:32:27 by yousong           #+#    #+#             */
/*   Updated: 2023/12/01 14:32:33 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct t_node
{
	char			*content;
	struct t_node	*next;
}	t_node;

char	*get_next_line(int fd);
void	ft_list(t_node **stash, int fd);
void	ft_append(t_node **stash, char *buf);
char	*ft_line(t_node *stash);
void	ft_leftover(t_node **stash);
int		ft_newline(t_node *stash);
int		count_to_newline(t_node *stash);
t_node	*ft_last_t_node(t_node *stash);
void	ft_strcpy(t_node *stash, char *next_line);
void	ft_dealloc(t_node **stash, t_node *clean, char *buf);

#endif
