/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:38:00 by yousong           #+#    #+#             */
/*   Updated: 2025/02/18 01:20:49 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	heredoc_expander(char **line, t_env *env)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_token(line, i, env);
			if ((*line)[i] == '$')
				i--;
		}
	}
}

static void	get_input(int fd, char *limiter, t_env *env)
{
	char	*input;
	char	*limiter_tmp;

	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			printf("\nminishell: warning: here-document delimited by"
				" end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (is_equal(limiter_tmp, input))
		{
			free(input);
			break ;
		}
		heredoc_expander(&input, env);
		ft_putstr_fd(input, fd);
		free(input);
	}
	free(limiter_tmp);
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
			get_input(fd, cmd->input[1], cmd->env);
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
		if (WIFEXITED(statloc))
			g_exit_stat = WEXITSTATUS(statloc);
		else if (WIFSIGNALED(statloc))
			g_exit_stat = 128 + WTERMSIG(statloc);
		set_echoctl(1);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		set_handler(heredoc_sigint, NULL);
		heredoc_unit(cmd);
	}
	return (g_exit_stat);
}
