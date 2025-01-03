/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:48:05 by yousong           #+#    #+#             */
/*   Updated: 2023/10/31 15:27:32 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*b;

	b = (char *)str;
	while (n > 0)
	{
		b[n - 1] = c;
		n--;
	}
	return (b);
}

/*int	main(void)
{
	char	str[50] = "supercalifragilistic";

	ft_memset(str, '$', 7);
	printf("%s\n", str);

	char	str2[50] = "supercalifragilistic";
	memset(str2, '$', 6);
	printf("%s", str2);
	return (0);
}*/
