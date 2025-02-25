/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:16:08 by yousong           #+#    #+#             */
/*   Updated: 2025/02/25 03:55:09 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static char	**parse_path(char *cmd, t_env *env)
{
	char	**parsed_path;
	char	*tmp;
	int		i;

	tmp = get_env("PATH", env);
	if (tmp == NULL)
	{
		err_print(cmd, ": No such file or directory", 0, 127);
		g_exit_stat = 127;
		exit(g_exit_stat);
	}
	parsed_path = ft_split(tmp, ':');
	i = -1;
	while (parsed_path[++i])
	{
		tmp = parsed_path[i];
		parsed_path[i] = ft_strjoin(parsed_path[i], "/");
		free(tmp);
	}
	return (parsed_path);
}

char	*find_path(t_cmd *cmd, int **fd)
{
	char	**env_path;
	char	*file_path;
	int		i;

	i = -1;
	if (access(cmd->input[0], R_OK | X_OK) == 0)
		return (ft_strdup(cmd->input[0]));
	env_path = parse_path(cmd->input[0], cmd->env);
	while (ft_strlen(cmd->input[0]) && env_path && env_path[++i])
	{
		file_path = ft_strjoin(env_path[i], cmd->input[0]);
		if (access(file_path, R_OK | X_OK) == 0)
		{
			path_dealloc(env_path);
			return (file_path);
		}
		else
			free(file_path);
	}
	if (env_path)
		path_dealloc(env_path);
	g_exit_stat = err_print(cmd->input[0], ": command not found", 0, 127);
	free_envlist(cmd->env);
	proc_dealloc(fd, cmd, NULL, 1);
	exit(g_exit_stat);
}

static void	exec_error(t_cmd *cmd, int **fd, char *path)
{
	g_exit_stat = err_print(path, ": ", "is a directory", 126);
	free_envlist(cmd->env);
	proc_dealloc(fd, cmd, NULL, 1);
	path_dealloc(&path);
	exit(g_exit_stat);
}

static void	run_builtin(t_cmd *cur_cmd, t_cmd *cmd, int child, int **fd)
{
	g_exit_stat = builtin_control(cur_cmd, fd, cmd->pipe_count + 1, child);
	free_envlist(cmd->env);
	proc_dealloc(fd, cmd, NULL, 1);
	exit(g_exit_stat);
}

void	execute_cmd(t_cmd *cmd, int child, int **fd)
{
	char	*path;
	t_cmd	*cur_cmd;
	int		redir_error;

	redir_error = set_redirect(cmd, fd, child);
	cur_cmd = find_cur_cmd(cmd, child);
	if (cur_cmd == NULL || redir_error)
	{
		free_envlist(cmd->env);
		proc_dealloc(fd, cmd, NULL, 1);
		exit(EXIT_SUCCESS);
	}
	free(set_fd(fd, cmd->pipe_count + 1, child));
	if (is_builtin(cur_cmd, child))
		run_builtin(cur_cmd, cmd, child, fd);
	path = find_path(cur_cmd, fd);
	free(cur_cmd->input[0]);
	cur_cmd->input[0] = ft_strdup(path);
	if (execve(path, cur_cmd->input, env_to_array(cur_cmd)) == -1)
		exec_error(cmd, fd, path);
}
