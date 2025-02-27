/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 02:05:51 by yousong           #+#    #+#             */
/*   Updated: 2025/02/27 22:22:07 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	free_fd(int **fd, int cnt)
{
	int	i;

	i = -1;
	while (fd && ++i < cnt + 1)
	{
		if (fd[i][0] > 2)
			close(fd[i][0]);
		if (fd[i][1] > 2)
			close(fd[i][1]);
		free(fd[i]);
	}
}

/* frees all command resources 
	removes temp heredoc files
	frees pid if exists
	free each element of pipe array and then the array
	then frees the whole cmd node */

void	proc_dealloc(int **fd, t_cmd *cmd, int *pid, int unlink)
{
	int		i;
	int		cnt;
	t_cmd	*tmp;

	cnt = cmd->pipe_count + 1;
	i = -1;
	if (unlink)
		unlink_file(cmd);
	if (pid)
		free(pid);
	free_fd(fd, cnt);
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

/* first reaches the cmd for the current child
	then looks for cmd node with word type 
	return that cmd node */

t_cmd	*find_cur_cmd(t_cmd *cmd, int child_num)
{
	while (cmd->unit_count < child_num)
		cmd = cmd->next;
	while (cmd && cmd->type != word)
	{
		if (cmd->unit_count > child_num)
			return (NULL);
		cmd = cmd->next;
	}
	return (cmd);
}

void	path_dealloc(char **env_path)
{
	int	i;

	i = -1;
	while (env_path[++i])
		free(env_path[i]);
	free(env_path);
}
