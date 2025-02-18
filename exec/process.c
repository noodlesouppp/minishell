/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:37:06 by yousong           #+#    #+#             */
/*   Updated: 2025/02/19 17:05:54 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static int	wait_for_child(t_cmd *cmd, pid_t *pid)
{
	int		statloc;
	int		last_stat;
	int		i;

	last_stat = 0;
	i = -1;
	while (++i < cmd->pipe_count + 1)
	{
		waitpid(pid[i], &statloc, 0);
		if (i == cmd->pipe_count)
		{
			if (WIFEXITED(statloc))
				last_stat = WEXITSTATUS(statloc);
			else if (WIFSIGNALED(statloc))
				last_stat = 128 + WTERMSIG(statloc);
		}
	}
	return (last_stat);
}

static void	parent(t_cmd *cmd, int **fd, pid_t *pid)
{
	t_cmd	*tmp;
	int		last_stat;

	tmp = cmd;
	while (tmp)
	{
		if (is_minishell(tmp->input[0]))
			break ;
		tmp = tmp -> next;
	}
	if (tmp == NULL)
		set_handler(print_newline, print_newline);
	close_fd(fd, cmd->pipe_count + 1, -1);
	last_stat = wait_for_child(cmd, pid);
	g_exit_stat = last_stat;
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
		builtin_control(cmd, fd, 1, 0);
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
