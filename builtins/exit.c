/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:02:19 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 10:05:16 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	arg_check(t_cmd *cmd, int cnt)
{
	int	i;

	i = -1;
	while (cnt > 1 && cmd->input[1][++i])
	{
		if (!ft_isdigit(cmd->input[1][i]) && cmd->input[1][i] != '-')
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			err_print("exit: ", cmd->input[1], ": numeric argument required", 2);
			g_exit_stat = 2;
			exit(g_exit_stat);
		}
	}
	if (cnt > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (err_print("exit: ", "too many arguments", NULL, 1));
	}
	return (0);
}

/* bash does modulo 256 for exit code */

int	ft_exit(t_cmd *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd->input[cnt])
		cnt++;
	if (arg_check(cmd, cnt))
		return (1);
	if (cmd->pipe_count == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cnt == 2)
		g_exit_stat = ((unsigned char)ft_atoi(cmd->input[1]));
	exit(g_exit_stat);
}
