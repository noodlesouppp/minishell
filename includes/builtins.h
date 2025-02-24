/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:42:18 by yousong           #+#    #+#             */
/*   Updated: 2025/02/24 18:07:14 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <sys/errno.h>

# include "environment.h"
# include "minishell.h"
# include "utils.h"

int		builtin_control(t_cmd *cmd, int **fd, int proc_cnt, int child_num);
int		is_builtin(t_cmd *cmd, int child_num);

int		echo(t_cmd *cmd);
int		env(t_cmd *cmd);
int		export(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		unset(t_cmd *cmd);
int		ft_exit(t_cmd *cmd, int **fd);

#endif