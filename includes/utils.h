/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:58:42 by yousong           #+#    #+#             */
/*   Updated: 2025/02/19 17:29:05 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

# include "minishell.h"
# include "../libs/libft/libft.h"

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

int			\
err_print(const char *prefix, const char *errmsg, char *postfix, int ret);
int			is_equal(char *s1, char *s2);
int			is_minishell(char *input);

#endif