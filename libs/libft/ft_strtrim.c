/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:47:57 by yousong           #+#    #+#             */
/*   Updated: 2023/11/08 04:55:29 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > 1)
		j--;
	if (i < j)
	{
		result = (char *)malloc(sizeof(char) * (j - i + 1));
		if (result)
			ft_strlcpy(result, s1 + i, (j - i + 1));
	}
	else
	{
		result = (char *)malloc(sizeof(char));
		if (result)
			result[0] = '\0';
	}
	return (result);
}

/*int	main(void)
{
	char	s1[] = "acbacbacbbaaHello, worldacbccbacbaba";
	char	set[] = "cba";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
