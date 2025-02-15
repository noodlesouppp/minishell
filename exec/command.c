/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:16:08 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:09:30 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	path_dealloc(char **env_path)
{
	int	i;

	i = -1;
	while (env_path[++i])
		free(env_path[i]);
	free(env_path);
}

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

static char	**parse_path(char *cmd, t_env *env)
{
	char	**parsed_path;
	char	*tmp;
	int		i;

	tmp = get_env("PATH", env);
	if (tmp == NULL)
	{
		err_print(cmd, ": No such file or directory", 0, 127);
		g_exit_status = 127;
		exit(g_exit_status);
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

char	*find_path(t_cmd *cmd)
{
	char	**env_path;
	char	*file_path;
	int		i;

	i = -1;
	if (access(cmd->input[0], R_OK | X_OK) == 0) {
		printf("cmd input: %s", cmd->input[0]);
		return (ft_strdup(cmd->input[0]));
	}
	env_path = parse_path(cmd->input[0], cmd->env);
	while (ft_strlen(cmd->input[0]) && env_path && env_path[++i])
	{
		file_path = ft_strjoin(env_path[i], cmd->input[0]);
		if (access(file_path, R_OK | X_OK) == 0)
		{
			path_dealloc(env_path);
			printf("file: %s", file_path);
			return (file_path);
		}
		else
			free(file_path);
	}
	if (env_path)
		path_dealloc(env_path);
	err_print(cmd->input[0], ": command not found", 0, 127);
	g_exit_status = 127;
	exit(EXIT_FAILURE);
}

void	execute_cmd(t_cmd *cmd, int child_num, int **fd)
{
	char	*path;
	t_cmd	*cur_cmd;

	if (set_redirect(cmd, fd, child_num))
		exit(EXIT_FAILURE);
	cur_cmd = find_cur_cmd(cmd, child_num);
	if (cur_cmd == NULL)
		exit(EXIT_SUCCESS);
	free(set_fd(fd, cmd->pipe_count + 1, child_num));
	if (is_builtin(cur_cmd, child_num))
	{
		g_exit_status = builtin_controller(cur_cmd, fd, cmd->pipe_count + 1, child_num);
		exit(g_exit_status);
	}
	path = find_path(cur_cmd);
	free(cur_cmd->input[0]);
	cur_cmd->input[0] = ft_strdup(path);
	if (execve(path, cur_cmd->input, env_to_array(cur_cmd)) == -1)
	{
		g_exit_status = err_print(path, ": ", "is a directory", 126);
		exit(g_exit_status);
	}
}
