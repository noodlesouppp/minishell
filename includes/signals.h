/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:38 by yousong           #+#    #+#             */
/*   Updated: 2025/02/20 13:14:53 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>

# include "minishell.h"

# ifndef ECHOCTL
#  define ECHOCTL 0x00000040
# endif

extern volatile sig_atomic_t	g_exit_stat;

/* signals.c */
void	set_handler(void (*sint_handler)(int s), void (*squit_handler)(int s));
void	quiet(int sig);
void	print_newline(int sig);
void	print_prompt(int sig);

/* signal_util.c */
void	set_echoctl(int mode);
void	heredoc_sigint(int sig);
void	heredoc_quiet(int sig);

#endif