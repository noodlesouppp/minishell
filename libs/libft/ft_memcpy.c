/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:49:11 by yousong           #+#    #+#             */
/*   Updated: 2023/11/02 16:23:57 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (dest);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	const char	src[25] = "copy this filthy casual";
	char	dest[25] = "smol";

	printf("%s\n", dest);
	ft_memcpy(dest, src + 7, 20);
	printf("%s\n", dest);
	return (0);
}*/
