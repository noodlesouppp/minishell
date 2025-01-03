/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:25:41 by yousong           #+#    #+#             */
/*   Updated: 2023/11/07 03:34:28 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			len;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	len = 0;
	if (src < dest)
	{
		len = n;
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (len < n)
		{
			d[len] = s[len];
			len++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	src[10] = "fivesfives";
	char	dest[30] = "DONTMOVEMEPLEASEDONTMOVEME";

	printf("%s\n", dest);
	ft_memmove(dest, src, 10);
	printf("%s", dest);
	return (0);
}*/
