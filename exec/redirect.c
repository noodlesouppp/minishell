/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:58:36 by yousong           #+#    #+#             */
/*   Updated: 2025/02/20 12:31:44 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/* mod 644 means you can read and write, and only others can read */

static void	set_output(t_cmd *cmd, int *fd)
{
	if (is_equal(cmd->input[0], ">>"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (is_equal(cmd->input[0], ">"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static void	set_input(t_cmd *cmd, int *fd)
{
	char	*file_name;
	char	*unit_cnt_tmp;

	if (is_equal(cmd->input[0], "<<"))
	{
		unit_cnt_tmp = ft_itoa(cmd->unit_count);
		file_name = ft_strjoin(".heredoc_tmp", unit_cnt_tmp);
		fd[0] = open(file_name, O_RDONLY);
		free(unit_cnt_tmp);
		free(file_name);
	}
	else if (is_equal(cmd->input[0], "<"))
		fd[0] = open(cmd->input[1], O_RDONLY);
}

/* scans cmds to find and process all redir operators */

int	*get_redirect_fd(t_cmd *cmd, int unit_cnt)
{
	int	*fd;

	fd = ft_calloc(2, sizeof(int));
	while (cmd)
	{
		if (cmd->unit_count == unit_cnt && cmd->type == redirect)
		{
			set_input(cmd, fd);
			set_output(cmd, fd);
			if (fd[0] < 0 || fd[1] < 0)
			{
				err_print(cmd->input[1], ": ", strerror(errno), 1);
				g_exit_stat = 1;
				free(fd);
				return (NULL);
			}
		}
		else if (cmd->unit_count > unit_cnt)
			break ;
		cmd = cmd->next;
	}
	return (fd);
}
