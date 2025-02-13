/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:05 by yousong           #+#    #+#             */
/*   Updated: 2025/02/03 23:52:42 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	err_print(char *prefix, char *errmsg, char *postfix, int return_val)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (prefix)
		ft_putstr_fd(prefix, STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	if (postfix)
		ft_putstr_fd(postfix, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (return_val);
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
