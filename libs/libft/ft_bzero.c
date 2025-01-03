/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:13:55 by yousong           #+#    #+#             */
/*   Updated: 2023/11/02 13:47:42 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <strings.h>
#include <string.h>*/
#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

/*int	main(void)
{
	char	str[50] = "PLEASE DONT REMOVE ME";
	char	str2[50] = "PLEASe DONT REMOVE ME";

	printf("%s\n", str);
	bzero(str, 6);
	printf("%s\n", str);
	printf("%s\n", str2);
	ft_bzero(str2, 6);
	printf("%s\n", str2);
}*/
