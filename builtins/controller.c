/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:41:21 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 01:34:27 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execute.h"

int	exec_builtin(t_cmd *cmd, int **fd)
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
		return (ft_exit(cmd, fd));
	else if (is_equal(cmd_input, "export"))
		return (export(cmd));
	else if (is_equal(cmd_input, "pwd"))
		return (pwd());
	else if (is_equal(cmd_input, "unset"))
		return (unset(cmd));
	else
		return (1);
}

/* if no pipes, builtin is executed in parent process, 
	so manual fd is required */

int	builtin_control(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int		*std_fd;
	t_cmd	*cur_cmd;

	cur_cmd = find_cur_cmd(cmd, child_num);
	if (cur_cmd == NULL)
		return (1);
	if (cmd->pipe_count == 0 && is_builtin(cur_cmd, child_num)
		&& !is_equal(cur_cmd->input[0], "exit"))
	{
		if (set_redirect(cmd, fd, child_num))
			return (1);
		std_fd = set_fd_builtin(fd, proc_cnt, child_num);
		set_handler(print_newline, print_newline);
	}
	cmd->env->exit_stat = exec_builtin(cur_cmd, fd);
	if (cmd->pipe_count == 0 && is_builtin(cur_cmd, child_num)
		&& !is_equal(cur_cmd->input[0], "exit"))
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[0]);
		close(std_fd[1]);
		free(std_fd);
	}
	return (cmd->env->exit_stat);
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
