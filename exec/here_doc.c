/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:38:00 by yousong           #+#    #+#             */
/*   Updated: 2025/02/03 23:48:30 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	heredoc_expander(char **line)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_token(line, i);
			if ((*line)[i] == '$')
				i--;
		}
	}
}

static void	get_input(int fd, char *limiter)
{
	char	*input;
	char	*limiter_tmp;

	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input || is_equal(limiter_tmp, input))
		{
			free(input);
			free(limiter_tmp);
			return ;
		}
		heredoc_expander(&input);
		ft_putstr_fd(input, fd);
		free(input);
	}
}

static void	heredoc_unit(t_cmd *cmd)
{
	char	*unit_cnt;
	char	*file_name;
	int		fd;

	while (cmd)
	{
		if (cmd->type == redirect && is_equal(cmd->input[0], "<<"))
		{
			unit_cnt = ft_itoa(cmd->unit_count);
			file_name = ft_strjoin(".heredoc_tmp", unit_cnt);
			fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
			if (fd < 0)
			{
				err_print("heredoc: tmp_err", ": ", strerror(errno), 1);
				break ;
			}
			get_input(fd, cmd->input[1]);
			close(fd);
			free(unit_cnt);
			free(file_name);
		}
		cmd = cmd->next;
	}
	exit(EXIT_SUCCESS);
}

int	heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		statloc;

	set_echoctl(0);
	pid = fork();
	if (pid != 0)
	{
		set_handler(heredoc_quiet, NULL);
		waitpid(pid, &statloc, 0);
		if (WEXITSTATUS(statloc) != 0)
			unlink_file(cmd);
		set_echoctl(1);
	}
	else
	{
		set_handler(heredoc_sigint, NULL);
		heredoc_unit(cmd);
	}
	if (g_env->exit_stat == 0)
		*(g_env->exit_stat) = WEXITSTATUS(statloc);
	return (WEXITSTATUS(statloc));
}