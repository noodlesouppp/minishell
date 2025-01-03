/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:45:20 by yousong           #+#    #+#             */
/*   Updated: 2023/11/09 05:40:31 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, long n, int len)
{
	int	neg;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
	}
	while (len > 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
	{
		str[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = ft_intlen(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, num, len);
	return (str);
}

/*int	main(void)
{
	int	tests[] = {0, 5, -11, 9, -456, -12345, -696969};
	int	i = 0;
	char	*str;

	while (i < 7)
	{
		str = ft_itoa(tests[i]);
		printf("test: %d, output: %s\n", tests[i], str);
		i++;
	}
	return (0);
}*/
