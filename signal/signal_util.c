/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:09 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 22:57:33 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../includes/signals.h"

void	heredoc_quiet(int sig)
{
	if (sig == SIGINT)
		g_sig_num = sig;
	rl_replace_line("", 1);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	g_sig_num = sig;
	if (sig == SIGINT)
		exit(128 + g_sig_num);
}

void	set_echoctl(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
