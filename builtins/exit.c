/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:02:19 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 04:50:24 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	arg_check(t_cmd *cmd, int cnt, int **fd)
{
	int	i;

	i = -1;
	while (cnt > 1 && cmd->input[1][++i])
	{
		if (!ft_isdigit(cmd->input[1][i]) && cmd->input[1][i] != '-')
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			err_print("exit: ", cmd->input[1], ": numeric arg required", 2);
			cmd->env->exit_stat = 2;
			free_envlist(cmd->env);
			proc_dealloc(fd, cmd, NULL, 0);
			exit(2);
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

int	ft_exit(t_cmd *cmd, int **fd)
{
	int	cnt;
	int	exit_code;

	cnt = 0;
	while (cmd->input[cnt])
		cnt++;
	if (arg_check(cmd, cnt, fd))
		return (1);
	if (cmd->pipe_count == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cnt == 2)
		cmd->env->exit_stat = ((unsigned char)ft_atoi(cmd->input[1]));
	exit_code = cmd->env->exit_stat;
	free_envlist(cmd->env);
	proc_dealloc(fd, cmd, NULL, 0);
	exit(exit_code);
}
