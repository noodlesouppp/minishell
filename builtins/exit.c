/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:02:19 by yousong           #+#    #+#             */
/*   Updated: 2025/02/13 17:35:45 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

// Add function to check for args

static int	arg_check(t_cmd *cmd, int cnt)
{
	int	i;

	i = -1;
	while (cnt > 1 && cmd->input[1][++i])
	{
		if (!ft_isdigit(cmd->input[1][i]) && cmd->input[1][i] != '-')
		{
			ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
			err_print(0, cmd->input[1], ": numeric argument required", 0);
			return (255);
		}
	}
	if (cnt > 2)
		return (err_print("exit: ", "too many arguments", NULL, 1));
	return (0);
}

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
		return((unsigned char)ft_atoi(cmd->input[1]));
	return (0);
}