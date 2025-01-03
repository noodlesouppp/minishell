/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:08:21 by yousong           #+#    #+#             */
/*   Updated: 2023/11/06 20:03:39 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	check;
	size_t			i;

	str = (unsigned char *)s;
	check = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == check)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	str[20] = "LLLLLLLWLLL";

	printf("%p\n", ft_memchr(str, 'W', 10));
	printf("%p\n", memchr(str, 'W', 10));
	return (0);
}*/
