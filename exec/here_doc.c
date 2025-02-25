/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:38:00 by yousong           #+#    #+#             */
/*   Updated: 2025/02/25 02:11:47 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	heredoc_expander(char **line, t_env *env)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_token(line, i, env);
			if (!(*line)[i])
				break ;
			if ((*line)[i] == '$')
				i--;
		}
		else
			i++;
	}
}

static void	get_input(int fd, char *limiter, t_env *env)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("\nminishell: warning: here-document delimited by"
				" end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(input);
			break ;
		}
		heredoc_expander(&input, env);
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
}

/* O_RDWR: open for reading and writing
	O_TRUNC: if file exists, truncate to zero len (safety)
	O_CREAT: create file if not exist 
	mod 777 makes all users read write exec */

static void	process_heredoc(t_cmd *cmd)
{
	char	*unit_cnt;
	char	*file_name;
	int		fd;

	unit_cnt = ft_itoa(cmd->unit_count);
	file_name = ft_strjoin(".heredoc_tmp", unit_cnt);
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
	{
		err_print("heredoc: tmp_err", ": ", strerror(errno), 1);
		free(unit_cnt);
		free(file_name);
		return ;
	}
	get_input(fd, cmd->input[1], cmd->env);
	close(fd);
	free(unit_cnt);
	free(file_name);
}

static void	heredoc_init(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	while (cmd)
	{
		if (cmd->type == redirect && is_equal(cmd->input[0], "<<"))
			process_heredoc(cmd);
		cmd = cmd->next;
	}
	free_envlist(head->env);
	proc_dealloc(NULL, head, NULL, 0);
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
		set_handler(heredoc_sigint, NULL);
		heredoc_init(cmd);
	}
	return (g_exit_stat);
}
