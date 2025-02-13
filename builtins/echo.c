/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:47:28 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:22:53 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	is_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = is_option(cmd->input[1]);
	while (cmd->input[++i + flag])
	{
		printf("%s", cmd->input[i + flag]);
		if (cmd->input[i + flag + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
