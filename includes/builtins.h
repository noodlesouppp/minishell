/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:42:18 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:21:48 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <sys/errno.h>

# include "../includes/environment.h"
# include "../includes/minishell.h"
# include "../includes/utils.h"

int		builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num);
int		is_builtin(t_cmd *cmd, int child_num);

int		echo(t_cmd *cmd);
int		env(void);
int		export(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		unset(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);

#endif