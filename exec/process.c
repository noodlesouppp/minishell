/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:37:06 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 01:00:53 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	unlink_file(t_cmd *cmd)
{
	int		cnt;
	int		i;
	char	*unit_cnt;
	char	*file_name;

	cnt = cmd->pipe_count + 1;
	i = -1;
	while (++i < cnt)
	{
		unit_cnt = ft_itoa(i);
		file_name = ft_strjoin(".heredoc_tmp", unit_cnt);
		if (access(file_name, F_OK) == 0)
			unlink(file_name);
		free(unit_cnt);
		free(file_name);
	}
}

static void	parent(t_cmd *cmd, int **fd, pid_t *pid)
{
	t_cmd	*tmp;
	int		statloc;
	int		i;

	tmp = cmd;
	i = -1;
	while (tmp)
	{
		if (is_minishell(cmd->input[0]))
			break ;
		tmp = tmp -> next;
	}
	if (tmp == NULL)
		set_handler(print_newline, print_newline);
	close_fd(fd, cmd->pipe_count + 1, -1);
	while (++i < cmd->pipe_count + 1)
		waitpid(pid[i], &statloc, 0);
	if (*(g_env->exit_stat) == 0)
		*(g_env->exit_stat) += (WEXITSTATUS(statloc));
	proc_dealloc(fd, cmd, pid);
}

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd)
{
	if (*child_num >= proc_cnt - 1 || (*child_num >= 0 && pid[*child_num] == 0))
		return (pid[*child_num]);
	(*child_num)++;
	pid[*child_num] = fork();
	return (fork_proc(proc_cnt, child_num, pid, fd));
}

void	proc_dealloc(int **fd, t_cmd *cmd, int *pid)
{
	int		i;
	int		cnt;
	t_cmd	*tmp;

	cnt = cmd->pipe_count + 1;
	i = -1;
	unlink_file(cmd);
	if (pid)
		free(pid);
	while (fd && ++i < cnt + 1)
		free(fd[i]);
	if (fd)
		free(fd);
	while (cmd)
	{
		i = -1;
		tmp = cmd->next;
		while (cmd->input[++i])
			free(cmd->input[i]);
		free(cmd->input);
		free(cmd);
		cmd = tmp;
	}
}

void	process(t_cmd *cmd)
{
	int		**fd;
	int		child_num;
	pid_t	*pid;

	*(g_env->exit_stat) = 0;
	set_echoctl(1);
	child_num = -1;
	if (heredoc(cmd))
	{
		proc_dealloc(NULL, cmd, NULL);
		return ;
	}
	fd = make_pipe(cmd);
	if (cmd->pipe_count == 0 && is_builtin(cmd, 0))
	{
		builtin_controller(cmd, fd, 1, 0);
		proc_dealloc(fd, cmd, NULL);
		return ;
	}
	pid = malloc(sizeof(pid_t) * ((cmd->pipe_count) + 1));
	set_handler(quiet, quiet);
	if (fork_proc((cmd->pipe_count) + 1, &child_num, pid, fd) != 0)
		parent(cmd, fd, pid);
	else
		execute_cmd(cmd, child_num, fd);
}