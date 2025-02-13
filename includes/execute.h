/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:38:05 by yousong           #+#    #+#             */
/*   Updated: 2025/02/13 19:31:37 by yousong          ###   ########.fr       */
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
void	process(t_cmd *cmd, int *exit_stat);
void	unlink_file(t_cmd *cmd);
void	proc_dealloc(int **fd, t_cmd *cmd, int *pid);

/* command.c */
void	execute_cmd(t_cmd *cmd, int child_num, int **fd, int *exit_stat);
char	*find_path(t_cmd *cmd, int *exit_stat);
t_cmd	*find_cur_cmd(t_cmd *cmd, int child_num);

/* here_doc.c */
int	heredoc(t_cmd *cmd, int *exit_stat);

/* redirect.c */
int	*get_redirect_fd(t_cmd *cmd, int unit_cnt, int *exit_stat);

/* set_fd.c */
int		**make_pipe(t_cmd *cmd);
int		set_redirect(t_cmd *cmd, int **fd, int child_num, int *exit_stat);
int		*set_fd(int **fd, int proc_cnt, int child_num);
void	close_fd(int **fd, int proc_cnt, int child_num);

#endif