/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 02:54:22 by yousong           #+#    #+#             */
/*   Updated: 2023/11/06 16:08:16 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dest[i])
		i++;
	if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	while (src[j] && (i + j < dstsize - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}

/*int	main(void)
{
	char	str1[15] = "sourcesource";
	char	str2[30] = "destdest";

	printf("%s\n", str2);
	ft_strlcat(str2, str1, 20);
	printf("%s\n", str2);
	return (0);
}*/
