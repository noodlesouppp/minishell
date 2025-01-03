/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:30:50 by yousong           #+#    #+#             */
/*   Updated: 2023/11/07 05:01:42 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (ft_strlen(src));
	while (i + 1 < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

/*int	main(void)
{
	char	str[20] = "sourcesourcesource";
	char	str2[25] = "dandandandandan";

	printf("%s\n", str2);
	ft_strlcpy(str2, str, 5);
	printf("%s", str2);
	return (0);
}*/
