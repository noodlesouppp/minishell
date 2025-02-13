/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:39:37 by yousong           #+#    #+#             */
/*   Updated: 2025/02/13 17:59:22 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

void	close_fd(int **fd, int proc_cnt, int child_num)
{
	int	i;

	i = -1;
	while (++i <= proc_cnt)
	{
		if (fd[i][1] == STDOUT_FILENO || fd[i][0] == STDIN_FILENO)
			continue ;
		if (i == child_num)
		{
			close(fd[i][1]);
		}
		else if (i == child_num + 1)
		{
			close(fd[i][0]);
		}
		else
		{
			close(fd[i][1]);
			close(fd[i][0]);
		}
	}
}

int	*set_fd(int **fd, int proc_cnt, int child_num)
{
	int	*std_fd;

	std_fd = malloc(sizeof(int) * 2);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	close_fd(fd, proc_cnt, child_num);
	dup2(fd[child_num][0], STDIN_FILENO);
	dup2(fd[child_num + 1][1], STDOUT_FILENO);
	return (std_fd);
}

int	set_redirect(t_cmd *cmd, int **fd, int child_num, int *exit_stat)
{
	int	*redir_fd;

	redir_fd = get_redirect_fd(cmd, child_num, exit_stat);
	if (redir_fd == NULL)
		return (1);
	if (redir_fd[0] > 0)
	{
		if (fd[child_num][0] != STDIN_FILENO)
			close(fd[child_num][0]);
		fd[child_num][0] = redir_fd[0];
	}
	if (redir_fd[1] > 0)
	{
		if (fd[child_num + 1][1] != STDOUT_FILENO)
			close(fd[child_num + 1][1]);
		fd[child_num + 1][1] = redir_fd[1];
	}
	free(redir_fd);
	return (0);
}

int	**make_pipe(t_cmd *cmd)
{
	int		**fd;
	int		i;

	i = -1;
	fd = malloc(sizeof(int *) * ((cmd->pipe_count) + 2));
	while (++i < (cmd->pipe_count) + 2)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		if (i == 0)
		{
			close(fd[i][0]);
			fd[i][0] = STDIN_FILENO;
		}
		else if (i == (cmd->pipe_count) + 1)
		{
			close(fd[i][1]);
			fd[i][1] = STDOUT_FILENO;
		}
	}
	return (fd);
}