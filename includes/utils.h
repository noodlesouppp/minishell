/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:58:42 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:39:40 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

# include "../includes/minishell.h"
# include "../libs/libft/libft.h"

int			\
err_print(char *prefix, char *errmsg, char *postfix, int return_val);
int			is_equal(char *s1, char *s2);
int			is_minishell(char *input);

#endif