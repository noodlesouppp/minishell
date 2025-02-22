/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:41:21 by yousong           #+#    #+#             */
/*   Updated: 2025/02/20 13:26:52 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execute.h"

int	exec_builtin(t_cmd *cmd)
{
	char	*cmd_input;

	cmd_input = cmd->input[0];
	if (is_equal(cmd_input, "cd"))
		return (cd(cmd));
	else if (is_equal(cmd_input, "echo"))
		return (echo(cmd));
	else if (is_equal(cmd_input, "env"))
		return (env(cmd));
	else if (is_equal(cmd_input, "exit"))
		return (ft_exit(cmd));
	else if (is_equal(cmd_input, "export"))
		return (export(cmd));
	else if (is_equal(cmd_input, "pwd"))
		return (pwd());
	else if (is_equal(cmd_input, "unset"))
		return (unset(cmd));
	else
		return (1);
}

/* if no pipes, builtin is executed in parent process, so manual fd is required */

int	builtin_control(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int		*std_fd;
	t_cmd	*cur_cmd;

	cur_cmd = find_cur_cmd(cmd, child_num);
	if (cur_cmd == NULL)
		return (1);
	if (cmd->pipe_count == 0 && is_builtin(cur_cmd, child_num))
	{
		if (set_redirect(cmd, fd, child_num))
			return (1);
		std_fd = set_fd(fd, proc_cnt, child_num);
		set_handler(print_newline, print_newline);
	}
	g_exit_stat = exec_builtin(cur_cmd);
	if (cmd->pipe_count == 0 && is_builtin(cur_cmd, child_num))
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		free(std_fd);
	}
	return (g_exit_stat);
}

int	is_builtin(t_cmd *cmd, int child_num)
{
	char	*cmd_input;

	cmd = find_cur_cmd(cmd, child_num);
	if (cmd == NULL)
		return (0);
	cmd_input = cmd->input[0];
	if (is_equal(cmd_input, "cd"))
		return (1);
	else if (is_equal(cmd_input, "echo"))
		return (1);
	else if (is_equal(cmd_input, "env"))
		return (1);
	else if (is_equal(cmd_input, "exit"))
		return (1);
	else if (is_equal(cmd_input, "export"))
		return (1);
	else if (is_equal(cmd_input, "pwd"))
		return (1);
	else if (is_equal(cmd_input, "unset"))
		return (1);
	else
		return (0);
}
