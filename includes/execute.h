/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:38:05 by yousong           #+#    #+#             */
/*   Updated: 2025/02/26 00:31:17 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <fcntl.h>

# include "minishell.h"
# include "parser.h"

typedef struct s_cmd	t_cmd;

/* process.c */
void	process(t_cmd *cmd);

/* command.c */
void	execute_cmd(t_cmd *cmd, int child_num, int **fd);
char	*find_path(t_cmd *cmd, int **fd);

/* here_doc.c */
int		heredoc(t_cmd *cmd);

/* redirect.c */
int		*get_redirect_fd(t_cmd *cmd, int unit_cnt);

/* set_fd.c */
int		**make_pipe(t_cmd *cmd);
int		set_redirect(t_cmd *cmd, int **fd, int child_num);
int		*set_fd_builtin(int **fd, int proc_cnt, int child_num);
void	close_fd(int **fd, int proc_cnt, int child_num);
void	set_fd(int **fd, int proc_cnt, int child_num);

/* exec_util.c */
void	proc_dealloc(int **fd, t_cmd *cmd, int *pid, int unlink);
void	unlink_file(t_cmd *cmd);
t_cmd	*find_cur_cmd(t_cmd *cmd, int child_num);
void	path_dealloc(char **env_path);

#endif