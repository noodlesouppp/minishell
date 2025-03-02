/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:37:06 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 22:25:42 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/* makes sure only exit stat of last command is returned */

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
	cmd->env->exit_stat = last_stat;
	proc_dealloc(fd, cmd, pid, 1);
}

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd)
{
	if (*child_num >= proc_cnt - 1 || (*child_num >= 0 && pid[*child_num] == 0))
		return (pid[*child_num]);
	(*child_num)++;
	pid[*child_num] = fork();
	return (fork_proc(proc_cnt, child_num, pid, fd));
}

static void	process_fork(t_cmd *cmd, int *child_num, pid_t *pid, int **fd)
{
	if (fork_proc((cmd->pipe_count) + 1, child_num, pid, fd) != 0)
		parent(cmd, fd, pid);
	else
	{
		free(pid);
		execute_cmd(cmd, *child_num, fd);
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
		proc_dealloc(NULL, cmd, NULL, 1);
		return ;
	}
	fd = make_pipe(cmd);
	if (cmd->pipe_count == 0 && is_builtin(cmd, 0))
	{
		builtin_control(cmd, fd, 1, 0);
		proc_dealloc(fd, cmd, NULL, 1);
		return ;
	}
	pid = malloc(sizeof(pid_t) * ((cmd->pipe_count) + 1));
	set_handler(quiet, quiet);
	process_fork(cmd, &child_num, pid, fd);
}
