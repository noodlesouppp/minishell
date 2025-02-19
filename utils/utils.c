/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:05 by yousong           #+#    #+#             */
/*   Updated: 2025/02/19 21:40:19 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	err_print(const char *prefix, const char *errmsg, char *postfix, int ret)
{
	if (!prefix)
		prefix = "";
	if (!errmsg)
		errmsg = strerror(errno);
	if (!postfix)
		postfix = "";
	printf("minishell: %s%s%s\n", prefix, errmsg, postfix);
	return (ret);
}

int	is_minishell(char *input)
{
	int	length;

	length = ft_strlen(input);
	if (length >= 9)
	{
		return (ft_memcmp(input + length - 10, "minishell", 10));
	}
	return (0);
}

int	is_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (0);
		i++;
	}
	return (1);
}
